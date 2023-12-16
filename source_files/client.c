/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 08:45:49 by dsylvain          #+#    #+#             */
/*   Updated: 2023/12/16 18:46:39 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

int	client_parse_args(int argc, char **argv, pid_t *server_pid,
	char string_buff[])
{
	if (argc > 3 || argc == 1)
		return (0);
	if (!is_valid_pid(argv[1]))
		return (0);
	*server_pid = ft_atoi(argv[1]);
	if (argc > 2 && argv[2][0])
	{
		ft_strlcpy(string_buff, argv[2], ft_strlen(argv[2]) + 1);
		string_buff[ft_strlen(argv[2])] = '\n';
	}
	else
		string_buff = NULL;
	return (1);
}

void	transmit_string_buff(char string_buff[], pid_t server_pid)
{
	// ft_printf("input_string: >%s<\n", string_buff);
	kill(server_pid, SIGUSR2);
	usleep(DELAY);
	transmit_string_length(string_buff, server_pid);
}

// TODO: emission of '\0' to signal End Of Transmission
int	transmission_loop(char string_buff[], char **input_string, pid_t server_pid)
{
	int					bytes_read;

	while (1)
	{
		if (string_buff[0])
			transmit_string_buff(string_buff, server_pid);
		bytes_read = read(0, string_buff, 5000);
		if (bytes_read == -1)
			return (0);
		else if (bytes_read == 0 || !string_buff[0])
			return (0);
		else
			string_buff[bytes_read] = '\0';
		input_string = NULL;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	pid_t				server_pid;
	char				*input_string;
	char				string_buff[5000];
	struct sigaction	sa_1;
	struct sigaction	sa_2;

	ft_memset(string_buff, '\0', 5000);
	if (!client_parse_args(argc, argv, &server_pid, string_buff))
		return (display_error(), 255);
	if (!initialize_sigaction_struct(&sa_1, &sa_2))
		return (display_error(), 255);
	// ft_printf("Server PID: %i\n", server_pid);
	sleep(1);
	if (!transmission_loop(string_buff, &input_string, server_pid))
		return (255);
	return (0);
}

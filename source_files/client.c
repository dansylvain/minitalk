/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 08:45:49 by dsylvain          #+#    #+#             */
/*   Updated: 2023/12/15 20:39:50 by dan              ###   ########.fr       */
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

void	convert_string_length_to_binary(size_t string_length, pid_t server_pid)
{
	int	i;
	int	bit;
	
	bit = 0;
	i = 23;
	while (i >= 0)
	{
		bit = (string_length >> i) & 1;
		printf("bit: %i\n", bit);
		if (bit == 0)
			kill(server_pid, SIGUSR1);
		else
			kill(server_pid, SIGUSR2);
		i--;
		pause();
	}
	ft_printf("string_length: %i\n", string_length);
}


void	transmit_string_length(char string_buff[], pid_t server_pid)
{
	int	string_length;

	string_length = ft_strlen(string_buff);
	convert_string_length_to_binary(string_length, server_pid);
}

void	transmit_string_buff(char string_buff[], pid_t server_pid)
{
	ft_printf("input_string: >%s<\n", string_buff);
	kill(server_pid, SIGUSR2);
	pause();
	transmit_string_length(string_buff, server_pid);
}

int	main(int argc, char **argv)
{
	pid_t				server_pid;
	char				*input_string;
	char				string_buff[5000];
	int					bytes_read;
	struct sigaction	sa_1;
	struct sigaction	sa_2;

	ft_memset(string_buff, '\0', 5000);
	if (!client_parse_args(argc, argv, &server_pid, string_buff))
		return (display_error(), 255);
	if (!initialize_sigaction_struct(&sa_1, &sa_2))
		return (display_error(), 255);
	ft_printf("Server PID: %i\n", server_pid);
	sleep(1);
	while (1)
	{
		if (string_buff[0])
			transmit_string_buff(string_buff, server_pid);
		bytes_read = read(0, string_buff, 5000);
		if (bytes_read == -1)
			return (display_error(), 255);
		else if (bytes_read == 0 || !string_buff[0])
			return (0);
		else
			string_buff[bytes_read] = '\0';
		input_string = NULL;
	}
	return (0);
}

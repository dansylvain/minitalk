/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsylvain <dsylvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 08:45:49 by dsylvain          #+#    #+#             */
/*   Updated: 2023/12/23 17:21:36 by dsylvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

int	g_client_binary = 0;

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

void	transmit_string_length(char string_buff[], pid_t server_pid)
{
	int	string_length;
	int	i;
	int	bit;

	string_length = ft_strlen(string_buff) - 1;
	bit = 0;
	i = 23;
	while (i >= 0)
	{
		g_client_binary = 0;
		bit = (string_length >> i) & 1;
		if (bit == 0)
		{
			kill(server_pid, SIGUSR1);
			wait_signal();
		}
		else if (bit == 1)
		{
			kill(server_pid, SIGUSR2);
			wait_signal();
		}
		g_client_binary = 0;
		i--;
	}
}

void	transmit_string_buff(char string_buff[], pid_t server_pid)
{
	while (g_client_binary == 0)
	{
		kill(server_pid, SIGUSR2);
		usleep(300);
	}
	g_client_binary = 0;
	transmit_string_length(string_buff, server_pid);
	while (g_client_binary == 0)
	{
	}
	g_client_binary = 0;
}

// TODO: emission of '\0' to signal End Of Transmission
int	transmission_loop(char string_buff[], char **input_string, pid_t server_pid)
{
	int					bytes_read;

	while (1)
	{
		if (string_buff[0])
			transmit_string_buff(string_buff, server_pid);
		ft_printf("> ");
		bytes_read = read(0, string_buff, 100000);
		if (bytes_read == -1)
			return (0);
		if (bytes_read == 0 || !string_buff[0])
		{
			ft_printf("why not?\n");
			return (0);
		}
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
	char				string_buff[100000];
	struct sigaction	sa_1;
	struct sigaction	sa_2;

	ft_memset(string_buff, '\0', 100000);
	ft_printf("client_pid: %i\n", getpid());
	if (!client_parse_args(argc, argv, &server_pid, string_buff))
		return (display_error(), 255);
	if (!initialize_sigaction_struct(&sa_1, &sa_2))
		return (display_error(), 255);
	sleep(1);
	if (!transmission_loop(string_buff, &input_string, server_pid))
		return (255);
	return (0);
}

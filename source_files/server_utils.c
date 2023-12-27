/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsylvain <dsylvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 05:47:16 by dsylvain          #+#    #+#             */
/*   Updated: 2023/12/27 13:01:42 by dsylvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

void	display_error(void)
{
	write(2, "Error\n", 6);
}

void	wait_signal_server(void)
{
	while (g_server_binary[0] == -1)
	{
	}
	g_server_binary[0] = -1;
}

int	initialize_sigaction_struct(struct sigaction *sa_1, struct sigaction *sa_2)
{
	sa_1->sa_sigaction = server_signal_handler;
	sigemptyset(&sa_1->sa_mask);
	sa_1->sa_flags = SA_SIGINFO;
	sa_2->sa_sigaction = server_signal_handler;
	sigemptyset(&sa_2->sa_mask);
	sa_2->sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, sa_1, NULL) == -1)
		return (0);
	if (sigaction(SIGUSR2, sa_2, NULL) == -1)
		return (0);
	return (1);
}

void	build_command_string(char command[], char *server_pid_str,
	char *input_string)
{
	char	quote[2];
	char	space[2];

	quote[0] = '\"';
	quote[1] = '\0';
	space[0] = ' ';
	space[1] = '\0';
	ft_strlcat(command, "./client ", 10);
	ft_strlcat(command, server_pid_str, 10 + ft_strlen(server_pid_str));
	if (input_string)
	{
		ft_strlcat(command, space, ft_strlen(command) + 2);
		ft_strlcat(command, quote, ft_strlen(command) + 2);
		ft_strlcat(command, input_string, ft_strlen(command)
			+ ft_strlen(input_string) + 1);
		ft_strlcat(command, quote, ft_strlen(command) + 2);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 06:34:05 by dsylvain          #+#    #+#             */
/*   Updated: 2023/12/20 19:41:21 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

void	display_error(void)
{
	write(2, "Error\n", 6);
}

int	is_valid_pid(char *argv_one)
{
	int	i;

	if (ft_atoi(argv_one) < 0)
		return (0);
	i = 0;
	while (argv_one[i])
	{
		if (!ft_isdigit(argv_one[i])
			&& argv_one[i] != '-' && argv_one[i] != '+')
			return (0);
		if ((argv_one[i] == '-' || argv_one[i] == '+')
			&& (argv_one[i + 1] == '-' || argv_one[i + 1] == '+'))
			return (0);
		if ((argv_one[i] == '-' || argv_one[i] == '+')
			&& ft_isdigit(argv_one[i - 1]))
			return (0);
		i++;
	}
	return (1);
}

int	initialize_sigaction_struct(struct sigaction *sa_1, struct sigaction *sa_2)
{
	sa_1->sa_sigaction = client_signal_handler_1;
	sigemptyset(&sa_1->sa_mask);
	sa_1->sa_flags = SA_SIGINFO;
	sa_2->sa_sigaction = client_signal_handler_2;
	sigemptyset(&sa_2->sa_mask);
	sa_2->sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, sa_1, NULL) == -1)
		return (0);
	if (sigaction(SIGUSR2, sa_2, NULL) == -1)
		return (0);
	return (1);
}

void	transmit_string_length(char string_buff[], pid_t server_pid)
{
	int	string_length;
	int	i;
	int	bit;
	
	string_length = ft_strlen(string_buff);
	bit = 0;
	i = 23;
	while (i >= 0)
	{
		bit = (string_length >> i) & 1;
		if (bit == 0 && g_client_binary == 0)
		{
			kill(server_pid, SIGUSR1);
			ft_printf("client > SIGUSR1\n");
			g_client_binary = 1;
		}
		else if (bit == 1 && g_client_binary == 0)
		{
			kill(server_pid, SIGUSR2);
			ft_printf("client > SIGUSR2\n");
			g_client_binary = 1;
		}
		i--;
	}
	ft_printf("mon ami string_length: %i\n", string_length);
}

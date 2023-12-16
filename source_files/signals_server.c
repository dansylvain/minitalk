/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_server.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 07:22:27 by dan               #+#    #+#             */
/*   Updated: 2023/12/16 18:15:21 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

// TODO: add logic to filter processes transmission 
void	server_signal_handler_1(int signal_number,
	siginfo_t *info, void *context)
{
	if (g_server_binary[1] == -1 || g_server_binary[1] == info->si_pid)
	{
		ft_printf("holala, %i\n", info->si_pid);
		g_server_binary[1] = info->si_pid;
	}
	kill(info->si_pid, SIGUSR2);
	g_server_binary[0] = 0;
	ft_printf("s:0");
}

void	server_signal_handler_2(int signal_number,
	siginfo_t *info, void *context)
{
	if (g_server_binary[1] == -1 || g_server_binary[1] == info->si_pid)
	{
		ft_printf("holala, %i\n", info->si_pid);
		g_server_binary[1] = info->si_pid;
	}
	kill(info->si_pid, SIGUSR2);
	g_server_binary[0] = 1;
	ft_printf("s:1");
}

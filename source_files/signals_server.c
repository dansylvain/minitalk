/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_server.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 07:22:27 by dan               #+#    #+#             */
/*   Updated: 2023/12/21 16:00:22 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

// TODO: add logic to filter processes transmission 
void	server_signal_handler(int signal_number,
	siginfo_t *info, void *context)
{
	g_server_binary[0] = 0;

	if (g_server_binary[0] == 0)
	{
		g_server_binary[1] = info->si_pid;
		// ft_printf("info->booms: >%i<\n", g_server_binary[1]);
	}
	
	if (g_server_binary[1] == info->si_pid)
	{
		if (signal_number == 10)
		{
			g_server_binary[0] = 0;
			ft_printf("incoming SIGUSR1\n");
		}
		else if (signal_number == 12)
		{
			g_server_binary[0] = 1;
			ft_printf("incoming SIGUSR2\n");
		}
	}
	
}

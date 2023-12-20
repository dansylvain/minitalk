/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_server.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 07:22:27 by dan               #+#    #+#             */
/*   Updated: 2023/12/20 17:56:31 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

// TODO: add logic to filter processes transmission 
void	server_signal_handler(int signal_number,
	siginfo_t *info, void *context)
{
	static int client_pid = 0;

	if (client_pid == 0)
		client_pid = info->si_pid;
	
	if (client_pid == info->si_pid)
	{
		if (signal_number == 10)
			g_server_binary[0] = 0;
		else
			g_server_binary[0] = 1;
	}
	kill(info->si_pid, SIGUSR2);
}

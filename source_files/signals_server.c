/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_server.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsylvain <dsylvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 07:22:27 by dan               #+#    #+#             */
/*   Updated: 2023/12/20 12:39:47 by dsylvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

// TODO: add logic to filter processes transmission 
void	server_signal_handler(int signal_number,
	siginfo_t *info, void *context)
{
	static client_pid = -1;

	if (client_pid == -1 || client_pid == info->si_pid)
	{
		if (signal_number == 10)
			ft_printf("s:0\n");
		else
			ft_printf("s:1\n");
		client_pid = info->si_pid;
	}
	g_server_binary = 1;
	kill(info->si_pid, SIGUSR2);
}

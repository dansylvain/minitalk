/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_server.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsylvain <dsylvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 07:22:27 by dan               #+#    #+#             */
/*   Updated: 2023/12/16 12:49:50 by dsylvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

void	server_signal_handler_1(int signal_number,
	siginfo_t *info, void *context)
{
	kill(info->si_pid, SIGUSR2);
	g_server_binary = 0;
	ft_printf("s:0");
}

void	server_signal_handler_2(int signal_number,
	siginfo_t *info, void *context)
{
	kill(info->si_pid, SIGUSR2);
	g_server_binary = 1;
	ft_printf("s:1");
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_server.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsylvain <dsylvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 07:22:27 by dan               #+#    #+#             */
/*   Updated: 2023/12/16 08:34:10 by dsylvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

void	server_signal_handler_1(int signal_number,
	siginfo_t *info, void *context)
{
	// ft_printf("incoming SIGUSR1 (PID: %d)\n", info->si_pid);
	kill(info->si_pid, SIGUSR2);
	ft_printf("0");
}

void	server_signal_handler_2(int signal_number,
	siginfo_t *info, void *context)
{
	// ft_printf("incoming SIGUSR2 (PID: %d)\n", info->si_pid);
	kill(info->si_pid, SIGUSR2);
	ft_printf("1");
}

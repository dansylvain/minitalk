/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_server.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsylvain <dsylvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 07:22:27 by dan               #+#    #+#             */
/*   Updated: 2024/01/16 07:14:58 by dsylvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

/**========================================================================
 *                           server_signal_handler
 *! logic added to restrict incoming signals to one client at a time
 *! BUT mask to be added in sigaction struct
 *========================================================================**/
void	server_signal_handler(int signal_number,
	siginfo_t *info, void *context)
{
	if (signal_number == 2)
	{
		g_server_binary[0] = -2;
		return ;
	}
	g_server_binary[0] = 0;
	if (g_server_binary[0] == 0)
		g_server_binary[1] = info->si_pid;
	if (g_server_binary[1] == info->si_pid)
	{
		if (signal_number == 10)
			g_server_binary[0] = 0;
		else
			g_server_binary[0] = 1;
	}
	(void)context;
}

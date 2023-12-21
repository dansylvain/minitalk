/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_client.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 05:33:41 by dsylvain          #+#    #+#             */
/*   Updated: 2023/12/21 13:04:37 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

void	client_signal_handler_1(int signal_number,
	siginfo_t *info, void *context)
{
	g_client_binary = 1;
	ft_printf("incoming SIGUSR1\n");
}

void	client_signal_handler_2(int signal_number,
	siginfo_t *info, void *context)
{
	g_client_binary = 1;
	ft_printf("incoming SIGUSR2\n");
}

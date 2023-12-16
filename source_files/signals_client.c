/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_client.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 05:33:41 by dsylvain          #+#    #+#             */
/*   Updated: 2023/12/16 18:47:30 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

void	client_signal_handler_1(int signal_number,
	siginfo_t *info, void *context)
{
	// ft_printf("incoming SIGUSR1\n");
	usleep(DELAY);
}

void	client_signal_handler_2(int signal_number,
	siginfo_t *info, void *context)
{
	// ft_printf("incoming SIGUSR2\n");
	usleep(DELAY);
}

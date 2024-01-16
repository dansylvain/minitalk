/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_client.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsylvain <dsylvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 05:33:41 by dsylvain          #+#    #+#             */
/*   Updated: 2024/01/01 15:25:52 by dsylvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

/**========================================================================
 *                           client_signal_handler_1
 *========================================================================**/
void	client_signal_handler_1(int signal_number,
	siginfo_t *info, void *context)
{
	g_client_binary = 1;
	(void)context;
	(void)info;
	(void)signal_number;
}

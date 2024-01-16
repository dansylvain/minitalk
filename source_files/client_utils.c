/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsylvain <dsylvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 06:34:05 by dsylvain          #+#    #+#             */
/*   Updated: 2024/01/01 15:26:18 by dsylvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

/**========================================================================
 *                           display_error
 *========================================================================**/
void	display_error(void)
{
	write(2, "Error\n", 6);
}

/**========================================================================
 *                           is_valid_pid
 *========================================================================**/
int	is_valid_pid(char *argv_one)
{
	int	i;

	if (ft_atoi(argv_one) < 0)
		return (0);
	i = 0;
	while (argv_one[i])
	{
		if (!ft_isdigit(argv_one[i])
			&& argv_one[i] != '-' && argv_one[i] != '+')
			return (0);
		if ((argv_one[i] == '-' || argv_one[i] == '+')
			&& (argv_one[i + 1] == '-' || argv_one[i + 1] == '+'))
			return (0);
		if ((argv_one[i] == '-' || argv_one[i] == '+')
			&& ft_isdigit(argv_one[i - 1]))
			return (0);
		i++;
	}
	return (1);
}

/**========================================================================
 *                           initialize_sigaction_struct
 *========================================================================**/
int	initialize_sigaction_struct(struct sigaction *sa_1, struct sigaction *sa_2)
{
	sa_1->sa_sigaction = client_signal_handler_1;
	sigemptyset(&sa_1->sa_mask);
	sa_1->sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, sa_1, NULL) == -1)
		return (0);
	if (sigaction(SIGUSR2, sa_1, NULL) == -1)
		return (0);
	return (1);
	(void)sa_2;
}

/**========================================================================
 *                           wait_signal
 *========================================================================**/
void	wait_signal(void)
{
	while (g_client_binary == 0)
	{
	}
	g_client_binary = 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsylvain <dsylvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 06:34:05 by dsylvain          #+#    #+#             */
/*   Updated: 2023/12/14 07:28:50 by dsylvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

void	display_error(void)
{
	write(2, "Error\n", 6);
}

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

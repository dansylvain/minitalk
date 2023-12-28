/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_transmission.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsylvain <dsylvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 13:17:38 by dsylvain          #+#    #+#             */
/*   Updated: 2023/12/28 06:08:30 by dsylvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

/**========================================================================
 *                     get_string_length_transmission
 *========================================================================**/
int	get_string_length_transmission(void)
{
	int	i;
	int	input_string_len;

	input_string_len = 0;
	i = 23;
	while (i >= 0)
	{
		while (g_server_binary[0] == -1)
		{
		}
		input_string_len = input_string_len << 1;
		input_string_len |= g_server_binary[0];
		g_server_binary[0] = -1;
		kill(g_server_binary[1], SIGUSR2);
		i--;
	}
	return (input_string_len);
}

/**========================================================================
 *                        get_char_transmission
 *========================================================================**/
char	get_char_transmission(void)
{
	int	i;
	int	c;

	c = 0;
	i = 7;
	while (i >= 0)
	{
		while (g_server_binary[0] == -1)
		{
		}
		c = c << 1;
		c |= g_server_binary[0];
		g_server_binary[0] = -1;
		kill(g_server_binary[1], SIGUSR2);
		i--;
	}
	return (c);
}

/**========================================================================
 *                      get_input_string_transmission
 *========================================================================**/
void	get_input_string_transmission(char **input_string,
		int input_string_len)
{
	int	i;

	i = 0;
	while (i < input_string_len)
	{
		(*input_string)[i] = get_char_transmission();
		i++;
	}
}

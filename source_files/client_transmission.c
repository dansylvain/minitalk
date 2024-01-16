/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_transmission.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsylvain <dsylvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 12:56:35 by dsylvain          #+#    #+#             */
/*   Updated: 2024/01/16 07:21:28 by dsylvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

/**========================================================================
 *                         TRANSMISSION FUNCTIONS
 *  function names self explanatory...
 *========================================================================**/
/**========================================================================
 *                           client_transmission.c
 *? replace with  lines below for mitalk V2
	int					bytes_read;

	while (1)
	{
		if (string_buff[0])
		{
			transmit_string_buff(string_buff, server_pid);
			ft_printf("TRANSMISSION COMPLETE\n");
 		ft_printf("> ");
		bytes_read = read(0, string_buff, 100000);
		if (bytes_read == -1)
			return (0);
		if (bytes_read == 1)
		{
			ft_memset(string_buff, '\0', 100000);
			continue ;
		}
		if (bytes_read == 0 || !string_buff[0])
			return (0);
		}
		wait_signal();
		input_string = NULL;
		return (1);
	}
 *========================================================================**/

/**========================================================================
 *                           transmission_loop
 *? confirmation message displayed after reveiving signal from server
 *========================================================================**/
int	transmission_loop(char string_buff[], char **input_string, pid_t server_pid)
{
	transmit_string_buff(string_buff, server_pid);
	wait_signal();
	ft_printf("TRANSMISSION COMPLETE\n");
	return (1);
	(void)input_string;
}

/**========================================================================
 *                           transmit_string_buff
 *========================================================================**/
void	transmit_string_buff(char string_buff[], pid_t server_pid)
{
	int	string_length;

	string_length = 0;
	while (g_client_binary == 0)
	{
		kill(server_pid, SIGUSR2);
		usleep(DELAY);
	}
	g_client_binary = 0;
	string_length = transmit_string_length(string_buff, server_pid);
	wait_signal();
	transmit_string(string_buff, server_pid, string_length);
	wait_signal();
	ft_memset(string_buff, '\0', 100000);
	g_client_binary = 0;
}

/**========================================================================
 *                           transmit_string_length
 *========================================================================**/
int	transmit_string_length(char string_buff[], pid_t server_pid)
{
	int	string_length;
	int	i;
	int	bit;

	string_length = ft_strlen(string_buff) - 1;
	bit = 0;
	i = 23;
	while (i >= 0)
	{
		bit = (string_length >> i) & 1;
		if (bit == 0)
		{
			kill(server_pid, SIGUSR1);
			wait_signal();
		}
		else if (bit == 1)
		{
			kill(server_pid, SIGUSR2);
			wait_signal();
		}
		g_client_binary = 0;
		i--;
	}
	return (string_length);
}

/**========================================================================
 *                           transmit_string
 *========================================================================**/
void	transmit_string(char string_buff[], pid_t server_pid, int string_length)
{
	int	i;

	i = 0;
	while (i < string_length)
	{
		transmit_char(string_buff[i], server_pid);
		i++;
	}
}

/**========================================================================
 *                           transmit_char
 *========================================================================**/
void	transmit_char(char octet, int server_pid)
{
	int		i;
	char	bit;

	i = 7;
	bit = 0;
	while (i >= 0)
	{
		bit = (octet >> i) & 1;
		if (bit == 0)
		{
			kill(server_pid, SIGUSR1);
			wait_signal();
		}
		else if (bit == 1)
		{
			kill(server_pid, SIGUSR2);
			wait_signal();
		}
		g_client_binary = 0;
		i--;
	}
}

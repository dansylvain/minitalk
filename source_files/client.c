/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsylvain <dsylvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 08:45:49 by dsylvain          #+#    #+#             */
/*   Updated: 2024/01/16 07:13:29 by dsylvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

int	g_client_binary = 0;

/**========================================================================
 *                                  main
 * stack is used to avoid unnecessary memory allocation
 * for bigger project, malloc to be implemented
 * although signals shouldn't be used for larger data set transmission
 *========================================================================**/
int	main(int argc, char **argv)
{
	pid_t				server_pid;
	char				*input_string;
	char				string_buff[100000];
	struct sigaction	sa_1;
	struct sigaction	sa_2;

	ft_memset(string_buff, '\0', 100000);
	if (!client_parse_args(argc, argv, &server_pid, string_buff))
		return (display_error(), 255);
	if (!initialize_sigaction_struct(&sa_1, &sa_2))
		return (display_error(), 255);
	if (!transmission_loop(string_buff, &input_string, server_pid))
		return (255);
	return (0);
}

/**========================================================================
 *                           client_parse_args
//? replace condition with line below for minitalk V2
// if (argc > 3 || argc == 1)
 *========================================================================**/
int	client_parse_args(int argc, char **argv, pid_t *server_pid,
	char string_buff[])
{
	if (argc != 3)
		return (0);
	if (!is_valid_pid(argv[1]))
		return (0);
	*server_pid = ft_atoi(argv[1]);
	if (argv[2][0] == '\0')
		return (0);
	else
	{
		ft_strlcpy(string_buff, argv[2], ft_strlen(argv[2]) + 1);
		string_buff[ft_strlen(argv[2])] = '\n';
	}
	string_buff = NULL;
	return (1);
}

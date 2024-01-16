/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsylvain <dsylvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 08:45:49 by dsylvain          #+#    #+#             */
/*   Updated: 2024/01/16 07:19:05 by dsylvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

int	g_server_binary[2] = {-1, 0};

/**========================================================================
 *                             MINITALK
 *?  two version of the project are available
 *?  comments show where to add/replace code to switch to version 2
 *  version 1 complies with 42 project restrictions
 *  version 2 expands it BUT uses forbidden functions (read and execlp)
 *  signal filtering could be added on bigger project (see signals_server.c)
 * 
 * global variables:
 * 		- server side : binary transmission value / client pid (table)
 * 		- client side : transmission coordination binary (single value)
 *========================================================================**/
/**========================================================================
 *                           main
//? add these two lines below initialize sigaction_struct for minitalk V2
	// if (!start_client(input_string, server_pid))
	// 	return (display_error(), 255);
 *========================================================================**/
int	main(int argc, char **argv)
{
	char				*input_string;
	pid_t				server_pid;
	struct sigaction	sa_1;
	struct sigaction	sa_2;

	input_string = NULL;
	if (!server_parse_args(argc, argv, &input_string))
		return (display_error(), 255);
	server_pid = getpid();
	ft_printf("Server PID: %i\n", server_pid);
	if (!initialize_sigaction_struct(&sa_1, &sa_2))
		return (display_error(), 255);
	if (!listening_loop(&input_string))
		return (display_error(), 255);
	return (0);
}

/**========================================================================
 *                           server_parse_args
//? replace condition with line below for minitalk V2
	// if (argc > 2)
 *========================================================================**/
int	server_parse_args(int argc, char **argv, char **input_string)
{
	if (argc > 1)
		return (0);
	if (argc == 1)
		return (*input_string = NULL, 1);
	if (argv[1] && argv[1][0])
		*input_string = argv[1];
	else
		*input_string = NULL;
	return (1);
}

/**========================================================================
 *                           listening_loop
 *========================================================================**/
int	listening_loop(char **input_string)
{
	int	input_string_len;

	while (1)
	{
		if (g_server_binary[0] == -2)
			return (0);
		g_server_binary[0] = -1;
		input_string_len = 0;
		wait_signal_server();
		if (g_server_binary[0] == -2)
			return (0);
		kill(g_server_binary[1], SIGUSR2);
		input_string_len = get_string_length_transmission();
		if (!create_input_string(input_string, input_string_len))
			return (0);
		usleep(DELAY);
		kill(g_server_binary[1], SIGUSR2);
		get_input_string_transmission(input_string, input_string_len);
		display_input_string(*input_string);
		usleep(DELAY);
		kill(g_server_binary[1], SIGUSR2);
	}
	return (1);
}

/**========================================================================
 *                           create_input_string
 *========================================================================**/
int	create_input_string(char **input_string, int input_string_len)
{
	if (input_string_len)
	{
		*input_string = (char *)ft_calloc(input_string_len + 1,
				sizeof(char));
		if (!*input_string)
			return (0);
		ft_memset(*input_string, '0', input_string_len);
	}
	else
		*input_string = NULL;
	return (1);
}

/**========================================================================
 *                           display_input_string
 *========================================================================**/
void	display_input_string(char *input_string)
{
	if (input_string)
	{
		ft_printf("%s\n", input_string);
		kill(g_server_binary[1], SIGUSR2);
		free(input_string);
		input_string = NULL;
	}
}

/**========================================================================
 *                           start_client
//? add this function for minitalk V2
 *========================================================================**/
// int	start_client(char *input_string, pid_t server_pid)
// {
// 	pid_t	child_pid;
// 	char	command[100000];
// 	char	*server_pid_str;
// 	int		i;

// 	ft_memset(command, '\0', 100000);
// 	server_pid_str = ft_itoa(server_pid);
// 	build_command_string(command, server_pid_str, input_string);
// 	free (server_pid_str);
// 	child_pid = fork();
// 	if (child_pid == -1)
// 		return (0);
// 	else if (child_pid == 0)
// 	{
// 		execlp("/usr/bin/terminator", "/usr/bin/terminator",
// 			"-e", command, NULL);
// 		return (0);
// 	}
// 	return (1);
// }

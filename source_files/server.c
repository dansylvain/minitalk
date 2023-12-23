/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsylvain <dsylvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 08:45:49 by dsylvain          #+#    #+#             */
/*   Updated: 2023/12/23 17:27:21 by dsylvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

int	g_server_binary[2] = {-1, 0};

/**========================================================================
 * starting the client could be done conditionnaly (with an argument)
 * I have to finish the base logic first.
 * this little extra would be implemented to aim for 'outstanding' evaluation 
 *========================================================================**/
int	server_parse_args(int argc, char **argv, char **input_string)
{
	if (argc > 2)
		return (0);
	if (argc == 1)
		return (*input_string = NULL, 1);
	if (argv[1] && argv[1][0])
		*input_string = argv[1];
	else
		*input_string = NULL;
	return (1);
}

int	start_client(char *input_string, pid_t server_pid)
{
	pid_t	child_pid;
	char	command[100000];
	char	*server_pid_str;
	int		i;

	ft_memset(command, '\0', 100000);
	server_pid_str = ft_itoa(server_pid);
	build_command_string(command, server_pid_str, input_string);
	free (server_pid_str);
	child_pid = fork();
	if (child_pid == -1)
		return (0);
	else if (child_pid == 0)
	{
		execlp("/usr/bin/terminator", "/usr/bin/terminator",
			"-e", command, NULL);
		return (0);
	}
	return (1);
}

//! I used usleep(300) after signal emission to fix issues
int	get_string_length_transmission(void)
{
	int	i;
	int	input_string_length;

	input_string_length = 0;
	i = 23;
	while (i >= 0)
	{
		while (g_server_binary[0] == -1)
		{
		}
		input_string_length = input_string_length << 1;
		input_string_length |= g_server_binary[0];
		g_server_binary[0] = -1;
		kill(g_server_binary[1], SIGUSR2);
		usleep(300);
		i--;
	}
	return (input_string_length);
}

// TODO: detect End Of Transmission to cancel mask
// TODO: set client_pid = -1 to cancel mask
// TODO: send a reception confirmation to client after printing message
int	listening_loop(char **input_string)
{
	int					input_string_len;

	while (1)
	{
		input_string_len = 0;
		while (g_server_binary[0] == -1)
		{
		}
		g_server_binary[0] = -1;
		kill(g_server_binary[1], SIGUSR2);
		input_string_len = get_string_length_transmission();
		ft_printf("input_string_len: %i\n", input_string_len);
		*input_string = (char *)ft_calloc(input_string_len, sizeof(char));
		if (!*input_string)
			return (0);
		kill(g_server_binary[1], SIGUSR2);
		free(*input_string);
	}
	return (1);
}

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
	if (!start_client(input_string, server_pid))
		return (display_error(), 255);
	if (!listening_loop(&input_string))
		return (display_error(), 255);
	return (0);
}

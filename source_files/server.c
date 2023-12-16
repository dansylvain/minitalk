/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsylvain <dsylvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 08:45:49 by dsylvain          #+#    #+#             */
/*   Updated: 2023/12/16 11:30:23 by dsylvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

int server_binary;

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

void	build_command_string(char command[], char *server_pid_str,
	char *input_string)
{
	char	quote[2];
	char	space[2];

	quote[0] = '\"';
	quote[1] = '\0';
	space[0] = ' ';
	space[1] = '\0';
	ft_strlcat(command, "./client ", 10);
	ft_strlcat(command, server_pid_str, 10 + ft_strlen(server_pid_str));
	if (input_string)
	{
		ft_strlcat(command, space, ft_strlen(command) + 2);
		ft_strlcat(command, quote, ft_strlen(command) + 2);
		ft_strlcat(command, input_string, ft_strlen(command)
			+ ft_strlen(input_string) + 1);
		ft_strlcat(command, quote, ft_strlen(command) + 2);
	}
}

int	start_client(char *input_string, pid_t server_pid)
{
	pid_t	child_pid;
	char	command[20000];
	char	*server_pid_str;
	int		i;

	ft_memset(command, '\0', 20000);
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

int	initialize_sigaction_struct(struct sigaction *sa_1, struct sigaction *sa_2)
{
	sa_1->sa_sigaction = server_signal_handler_1;
	sigemptyset(&sa_1->sa_mask);
	sa_1->sa_flags = SA_SIGINFO;
	sa_2->sa_sigaction = server_signal_handler_2;
	sigemptyset(&sa_2->sa_mask);
	sa_2->sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, sa_1, NULL) == -1)
		return (0);
	if (sigaction(SIGUSR2, sa_2, NULL) == -1)
		return (0);
	return (1);
}

// void get_input_string_length()
// {
// 	int i;
// 	int input_int;
	
// 	input_int = 0;
// 	i = 23;
// 	while (i >= 0)
// 	{
		
// 		pause();
// 		input_int = (input_int << i) | server_binary;
// 		printf("m%i\n", input_int);
// 		i--;
// 	}
// 	printf("\nConverted integer: %i\n", input_int);
// }

void get_input_string_length() {
    int i;
    int input_string_length;
	
    input_string_length = 0;
    i = 23;
    while (i >= 0)
    {
        pause(); 
        input_string_length = input_string_length << 1;
        input_string_length |= server_binary;
		ft_printf("f:%i\n", server_binary);
        i--;
    }
    ft_printf("\ninput_string_length: %i\n", input_string_length);
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
	ft_printf("%s\n", input_string);
	ft_printf("Server PID: %i\n", server_pid);
	if (!initialize_sigaction_struct(&sa_1, &sa_2))
		return (display_error(), 255);
	if (!start_client(input_string, server_pid))
		return (display_error(), 255);
	while (1)
	{
		
		pause();
		ft_printf("transfer started\n");
		get_input_string_length();
		
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dan <dan@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 08:26:17 by dsylvain          #+#    #+#             */
/*   Updated: 2023/12/15 18:41:52 by dan              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <stdio.h>

# include "libft/libft.h"
# include "get_next_line/get_next_line.h"
# include "ft_printf/ft_printf.h"

# define DELAY 1000000

extern	int server_binary;
extern	int client_binary;

void	display_error(void);
int		is_valid_pid(char *argv_one);
int		client_parse_args(int argc, char **argv, pid_t *server_pid,
			char string_buff[]);
int		server_parse_args(int argc, char **argv, char **input_string);
void	build_command_string(char command[], char *server_pid_str,
			char *input_string);
int		start_client(char *input_string, pid_t server_pid);
int		initialize_sigaction_struct(struct sigaction *sa_1,
			struct sigaction *sa_2);
void	client_signal_handler_1(int signal_number,
			siginfo_t *info, void *context);
void	client_signal_handler_2(int signal_number,
			siginfo_t *info, void *context);
void	server_signal_handler_1(int signal_number, siginfo_t *info,
			void *context);
void	server_signal_handler_2(int signal_number, siginfo_t *info,
			void *context);
#endif
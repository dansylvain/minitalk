/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsylvain <dsylvain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 08:26:17 by dsylvain          #+#    #+#             */
/*   Updated: 2023/12/28 07:26:30 by dsylvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <stdio.h>

# include "libft/libft.h"
# include "ft_printf/ft_printf.h"

# define DELAY 10000

extern int	g_server_binary[2];
extern int	g_client_binary;

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
void	server_signal_handler(int signal_number, siginfo_t *info,
			void *context);
void	server_signal_handler_2(int signal_number, siginfo_t *info,
			void *context);
int		transmit_string_length(char string_buff[], pid_t server_pid);
void	convert_string_length_to_binary(size_t string_length, pid_t server_pid);
void	build_command_string(char command[], char *server_pid_str,
			char *input_string);
void	wait_signal(void);
void	wait_signal_server(void);
int		transmission_loop(char string_buff[], char **input_string,
			pid_t server_pid);
void	get_input_string_transmission(char **input_string,
			int input_string_len);
int		get_string_length_transmission(void);
int		listening_loop(char **input_string);
int		create_input_string(char **input_string, int input_string_len);
void	display_input_string(char *input_string);
void	transmit_string_buff(char string_buff[], pid_t server_pid);
void	transmit_string(char string_buff[], pid_t server_pid,
			int string_length);
void	transmit_char(char octet, int server_pid);

#endif
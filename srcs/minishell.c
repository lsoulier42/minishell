/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 14:30:08 by lsoulier          #+#    #+#             */
/*   Updated: 2020/12/25 21:59:56 by louise           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

int     signal_received;
int     signal_value;

void    ctrlc_handler(int signum)
{
	signal_received = 1;
	write(STDIN_FILENO, "\r", 1);
	format_prompt();
	write(STDOUT_FILENO, "\n", 1);
	close(STDIN_FILENO);
	signal_value = signum;
}

int main(int argc, char *argv[], char *envp[])
{
	t_data		msh_data;
	char 		buffer[BUFFER_SIZE + 1];
	int 		read_return;
	int			end_of_command;
	char 		*trim_buffer;

	init_data(&msh_data, argv[0], envp);
	read_return = 1;
	while(!msh_data.exit_msh && read_return > 0)
	{
		format_prompt();
		ft_bzero(buffer, BUFFER_SIZE + 1);
		end_of_command = 0;
		while (!end_of_command)
		{
			signal_received = 0;
			signal_value = -1;
			signal(SIGINT, ctrlc_handler);
			read_return = read(0, buffer, BUFFER_SIZE);
			if (signal_received && signal_value == SIGINT)
			{
				dup(STDOUT_FILENO);
				read_return = 1;
				break ;
			}
			if (read_return <= 0)
				break ;
			buffer[read_return] = '\0';
			trim_buffer = ft_trim_char(buffer, "\n");
			if (!trim_buffer)
				break ;
			msh_data.parsed_input = parse_input(trim_buffer);
			free(trim_buffer);
			if (msh_data.parsed_input)
			{
				if (argc == 2 && ft_strcmp(argv[1], "debug") == 0)
					print_instructions_list(msh_data.parsed_input->begin_instructions);
				else
					execute_all_cmds(&msh_data);
				del_user_input(msh_data.parsed_input);
			}
			if (buffer[read_return - 1] == '\n')
				end_of_command = 1;
		}
	}
	ft_putstr("exit\n");
	ft_lstclear(&(msh_data.begin_env), &del_var);
	return (msh_data.exit_value);
}

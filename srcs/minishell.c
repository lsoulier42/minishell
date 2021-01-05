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

int     signal_received = 0;
int     signal_value = -1;

void    ctrlc_handler(int signum)
{
	signal_received = 1;
	write(0, "\n", 1);
	signal_value = SIGINT;
}

int main(int argc, char *argv[], char *envp[])
{
	t_data		msh_data;
	char 		buffer[BUFFER_SIZE + 1];
	int 		read_return;

	if (signal(SIGINT, ctrlc_handler) == SIG_ERR)
    {
	    exit(0);
    }
	init_data(&msh_data, argv[0], envp);
	while(!msh_data.exit_msh && !signal_received)
	{
		format_prompt(msh_data.begin_env);
		ft_bzero(buffer, BUFFER_SIZE + 1);
		read_return = 1;
		while (read_return != 0)
		{
			read_return = read(0, buffer, BUFFER_SIZE);
			if (read_return == -1)
				break ;
			buffer[read_return] = '\0';
			msh_data.parsed_input = parse_input(buffer);
			if (msh_data.parsed_input)
			{
				//print_instructions_list(msh_data.parsed_input->begin_instructions);
				execute_all_cmds(&msh_data);
				del_user_input(msh_data.parsed_input);
			}
			if (buffer[read_return - 1] == '\n' || signal_received)
				break;
		}
	}
	ft_lstclear(&(msh_data.begin_env), &del_var);
	return (msh_data.exit_value);
}

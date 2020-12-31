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

int main(int argc, char *argv[], char *envp[])
{
	t_data		msh_data;
	char 		buffer[BUFFER_SIZE + 1];
	int 		read_return;

	g_env_list_begin = set_env(envp);
	init_data(&msh_data);
	while(!msh_data.exit_msh)
	{
		format_prompt();
		ft_bzero(buffer, BUFFER_SIZE + 1);
		while ((read_return = read(0, buffer, BUFFER_SIZE)) != 0)
		{
			buffer[read_return] = '\0';
			msh_data.parsed_input = parse_input(buffer);
			if (msh_data.parsed_input)
			{
				if (expand_vars(msh_data))
				{
					//print_instructions_list(msh_data.parsed_input->begin_instructions);
					execute_all_cmds(&msh_data);
				}
				del_user_input(msh_data.parsed_input);
			}
			if (buffer[read_return - 1] == '\n')
				break;
		}
	}
	ft_lstclear(&g_env_list_begin, &del_var);
	return (0);
}

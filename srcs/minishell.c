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

	init_data(&msh_data, envp);
	while(!msh_data.exit_msh)
	{
		format_prompt(msh_data.begin_env);
		ft_bzero(buffer, BUFFER_SIZE + 1);
		while ((read_return = read(0, buffer, BUFFER_SIZE)) != 0)
		{
			buffer[read_return] = '\0';
			msh_data.parsed_input = parse_input(buffer);
			/* reduce_quote(msh_data.parsed_input);
			 * expand_var(msh_data.begin_env, msh_data.parsed_input);
			execute_cmd(msh_data, msh_data.parsed_input);*/
			if (buffer[read_return - 1] == '\n')
				break ;
		}
	}
	ft_lstclear(&msh_data.begin_env, &del_var);
	return (0);
}

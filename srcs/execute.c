/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 03:45:00 by lsoulier          #+#    #+#             */
/*   Updated: 2020/12/31 03:45:08 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_all_cmds(t_data *msh_data)
{
	t_list	*instructions;
	t_list	*pipes;
	t_cmd	*cmd;

	instructions = msh_data->parsed_input->begin_instructions;
	while (instructions)
	{
		pipes = get_instruction_pipes(instructions);
		while (pipes)
		{
			cmd = get_cmd(pipes);
			if (search_builtin(cmd))
				execute_builtin(msh_data, cmd);
			pipes = pipes->next;
		}
		instructions = instructions->next;
	}
	return (1);
}

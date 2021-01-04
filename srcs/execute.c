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
#include <stdio.h>

int execute_last_builtin(t_data *msh_data, t_cmd *cmd, int previous_fd)
{
    if (cmd->redirections[IN]->fd != STDIN_FILENO)
        dup2(STDIN_FILENO, cmd->redirections[IN]->fd);
    else if (previous_fd != -1)
        dup2(STDIN_FILENO, previous_fd);
    msh_data->last_return = execute_builtin(msh_data, cmd);
    return(msh_data->last_return);
}

int execute_cmd(t_data *msh_data, t_list *pipes, int fdstdin)
{
    t_cmd	*cmd;

    cmd = get_cmd(pipes);
    if (!open_redirections(&(cmd->redirections)))
        return (-1);
    if (!expand_vars(msh_data, cmd))
        return (-1);
    cmd->name = search_path(msh_data->begin_env, cmd->name);
    cmd->is_last = !pipes->next;
    if (cmd->name != NULL)
    {
        if (!pipes->next && search_builtin(cmd->name))
            fdstdin = execute_last_builtin(msh_data, cmd, fdstdin);
        else
            fdstdin = execute_pipe_cmd(msh_data, cmd, fdstdin);
    }
    else
        format_error("minishell", cmd->args[0], 0, "Command not found");
    close_redirections(cmd->redirections);
    return (fdstdin);
}

int execute_all_cmds(t_data *msh_data)
{
	t_list	*instructions;
	t_list	*pipes;
    int 	fdstdin;

    fdstdin = -1;
	instructions = msh_data->parsed_input->begin_instructions;
		while (instructions)
	{
		pipes = get_instruction_pipes(instructions);
		while (pipes)
		{
            fdstdin = execute_cmd(msh_data, pipes, fdstdin);
			if (fdstdin == -1)
			    return (0);
			pipes = pipes->next;
		}
		instructions = instructions->next;
	}
	return (1);
}

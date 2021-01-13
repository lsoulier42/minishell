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

int		execute_cmd(t_data *msh_data, t_list **begin_cpid, t_list *pipes, int previous_fd)
{
	t_cmd *cmd;

	cmd = get_cmd(pipes);
	cmd->is_last = !pipes->next;
	cmd->is_piped = previous_fd != -1;
	if (cmd->is_last && search_builtin(cmd->args[0]))
		previous_fd = execute_last_builtin(msh_data, cmd, previous_fd);
	else
		previous_fd = execute_pipe_cmd(msh_data, begin_cpid, cmd, previous_fd);
	close_redirections(cmd->redirections);
	return (previous_fd);
}

static void execute_all_cmds_cpid(t_data *msh_data, t_list *instructions)
{
	t_list 	*cpid;
	pid_t	child_pid;
	int		stat_loc;

	cpid = ((t_instruction*)instructions->content)->begin_cpid;
	if (cpid)
		child_pid = ((t_cpid *)cpid->content)->child_pid;
	if (cpid && child_pid != -1)
	{
		waitpid(child_pid, &stat_loc, 0);
		if (WIFEXITED(stat_loc))
		{
			msh_data->last_return = WEXITSTATUS(stat_loc);
			cpid = cpid->next;
			while (cpid)
			{
				kill(((t_cpid *) cpid->content)->child_pid, SIGTERM);
				cpid = cpid->next;
			}
		}
	}
}

static int 	execute_all_cmds_loop(t_data *msh_data, t_list *instructions)
{
	t_list	*pipes;
	t_list	**begin_cpid;

	int		previous_fd;

	previous_fd = -1;
	pipes = get_instruction_pipes(instructions);
	while (pipes)
	{
		begin_cpid = &(((t_instruction*)instructions->content)->begin_cpid);
		if (process_sub_system(msh_data, begin_cpid, pipes))
		{
			previous_fd = execute_cmd(msh_data,
									  begin_cpid, pipes, previous_fd);
			if (previous_fd == -1)
				return (0);
		}
		pipes = pipes->next;
	}
	return (1);
}

int		execute_all_cmds(t_data *msh_data)
{
	t_list	*instructions;


	instructions = msh_data->parsed_input->begin_instructions;
	while (instructions && g_signal_value != SIGINT)
	{
		if(!execute_all_cmds_loop(msh_data, instructions))
			return(0);
		execute_all_cmds_cpid(msh_data, instructions);
		sigquit_exec_handler();
		instructions = instructions->next;
	}
	return (1);
}

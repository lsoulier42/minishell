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

int		execute_last_builtin(t_data *msh_data, t_cmd *cmd, int previous_fd)
{
	if (cmd->redirections[IN]->fd != STDIN_FILENO)
	{
		if (dup2(STDIN_FILENO, cmd->redirections[IN]->fd) == -1)
			return (-1);
	}
	else if (previous_fd != -1)
	{
		if (dup2(STDIN_FILENO, previous_fd) == -1)
			return (-1);
	}
	msh_data->last_return = execute_builtin(msh_data, cmd);
	return (msh_data->last_return);
}

int		execute_pipe_cmd(t_data *msh_data, t_list **begin_cpid, t_cmd *cmd, int previous_fd)
{
	pid_t	cpid;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		return (-1);
	cpid = fork();
	if (cpid == 0)
		return (execute_child_process(msh_data, cmd, previous_fd, pipefd));
	else if (cpid != -1)
	{
		if (!add_cpid(begin_cpid, cpid))
			return (-1);
		return (execute_parent_process(msh_data, cmd, pipefd));
	}
	return (-1);
}

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

int 	process_sub_system(t_data *msh_data, t_list **begin_cpid, t_list *pipes)
{
	t_cmd *cmd;

	cmd = get_cmd(pipes);
	if (!expand_vars(msh_data, cmd) || !cmd->args[0])
		return (0);
	if (!parse_path_and_name(&cmd))
		return (0);
	if (!open_redirections(&(cmd->redirections)))
		return (0);
	if (!search_path(msh_data, &cmd))
	{
		if (!add_cpid(begin_cpid, -1))
			return (0);
		msh_data->last_return = 127;
		return (0);
	}
	return (1);
}

int		execute_all_cmds(t_data *msh_data)
{
	t_list	*instructions;
	t_list	*pipes;
	t_list	**begin_cpid;
	t_list 	*cpid;
	pid_t	child_pid;
	int		previous_fd;
	int		stat_loc;

	instructions = msh_data->parsed_input->begin_instructions;
	while (instructions && g_signal_value != SIGINT)
	{
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
		sigquit_exec_handler();
		instructions = instructions->next;
	}
	return (1);
}

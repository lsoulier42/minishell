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

int		execute_pipe_cmd(t_data *msh_data, t_cmd *cmd, int previous_fd)
{
	pid_t	cpid;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		return (-1);
	cpid = fork();
	if (cpid == 0)
		return (execute_child_process(msh_data, cmd, previous_fd, pipefd));
	else if (cpid != -1)
		return (execute_parent_process(msh_data, cmd, cpid, pipefd));
	return (-1);
}

int		execute_cmd(t_data *msh_data, t_cmd *cmd, int previous_fd, int is_last)
{
	if (!parse_path_and_name(&cmd))
		return (-1);
	if (!open_redirections(&(cmd->redirections)))
		return (-1);
	if (!search_path(msh_data, &cmd))
	{
		previous_fd = 0;
		msh_data->last_return = 127;
	}
	else
	{
		cmd->is_last = is_last;
		cmd->is_piped = previous_fd != -1;
		if (cmd->is_last && search_builtin(cmd->args[0]))
			previous_fd = execute_last_builtin(msh_data, cmd, previous_fd);
		else
			previous_fd = execute_pipe_cmd(msh_data, cmd, previous_fd);
	}
	close_redirections(cmd->redirections);
	return (previous_fd);
}

int		execute_all_cmds(t_data *msh_data)
{
	t_list	*instructions;
	t_list	*pipes;
	int		previous_fd;
	t_cmd	*cmd;

	instructions = msh_data->parsed_input->begin_instructions;
	while (instructions && g_signal_value != SIGINT)
	{
		previous_fd = -1;
		pipes = get_instruction_pipes(instructions);
		while (pipes && g_signal_value != SIGINT)
		{
			cmd = get_cmd(pipes);
			if (expand_vars(msh_data, cmd) && cmd->args[0])
			{
				previous_fd = execute_cmd(msh_data, cmd, previous_fd, !pipes->next);
				if (previous_fd == -1)
					return (0);
				sigquit_exec_handler();
			}
			pipes = pipes->next;
		}
		instructions = instructions->next;
	}
	return (1);
}

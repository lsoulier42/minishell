/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 14:24:18 by lsoulier          #+#    #+#             */
/*   Updated: 2021/01/04 14:24:28 by lsoulier         ###   ########.fr       */
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
		return (execute_parent_process(cmd, pipefd));
	}
	return (-1);
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

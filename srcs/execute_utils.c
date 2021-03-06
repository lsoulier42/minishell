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
	if (cmd->redirections[IN] != STDIN_FILENO)
	{
		if (dup2(STDIN_FILENO, cmd->redirections[IN]) == -1)
			return (ressource_error(msh_data, "dup2", RESSOURCE_ERROR, -1));
	}
	else if (previous_fd != -1)
	{
		if (dup2(STDIN_FILENO, previous_fd) == -1)
			return (ressource_error(msh_data, "dup2", RESSOURCE_ERROR, -1));
	}
	if (!cmd->is_piped || ft_strcmp(cmd->args[0], "exit") != 0)
		msh_data->last_return = execute_builtin(msh_data, cmd);
	return (msh_data->last_return);
}

int		execute_pipe_cmd(t_data *msh_data, t_list **begin_cpid,
	t_cmd *cmd, int previous_fd)
{
	pid_t	cpid;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		return (ressource_error(msh_data, "pipe", RESSOURCE_ERROR, -1));
	cpid = fork();
	if (cpid == 0)
		return (execute_child_process(msh_data, cmd, previous_fd, pipefd));
	else if (cpid != -1)
	{
		if (previous_fd != -1)
			close(previous_fd);
		if (!add_cpid(begin_cpid, cpid))
			return (-1);
		return (execute_parent_process(cmd, pipefd));
	}
	return (ressource_error(msh_data, "fork", RESSOURCE_ERROR, -1));
}

int		process_sub_system(t_data *msh_data, t_list **begin_cpid, t_list *pipes)
{
	t_cmd	*cmd;
	int		error;

	cmd = get_cmd(pipes);
	error = 0;
	if (!expand_vars(msh_data, cmd) || !cmd->args[0])
		error = 1;
	if (!error && !parse_path_and_name(&cmd))
		error = 1;
	if (!error && !search_path(msh_data, &cmd))
	{
		error = 1;
		add_cpid(begin_cpid, -1);
		msh_data->last_return = COMMAND_NOT_FOUND;
	}
	if (error)
		close_redirections(cmd->redirections);
	return (error == 0);
}

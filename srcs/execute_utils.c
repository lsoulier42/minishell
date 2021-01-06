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

int		execute_child_process_execve(t_data *msh_data,
	t_cmd *cmd, int pipefd[2])
{
	char	**envp;
	int		execve_return;

	envp = serialize_env(msh_data->begin_env);
	if (!envp)
		return (-1);
	execve_return = execve(cmd->name, cmd->args, envp);
	ft_free_double_tab(envp);
	close(pipefd[1]);
	return (execve_return);
}

int		child_file_handler(int redir_in_fd, int previous_fd, int pipefd_read)
{
	int error;

	error = 0;
	close(pipefd_read);
	if (redir_in_fd != STDIN_FILENO)
	{
		close(STDIN_FILENO);
		if (dup(redir_in_fd) == -1)
			error = 1;
		close(redir_in_fd);
		if (previous_fd != -1)
			close(previous_fd);
	}
	else if (previous_fd != -1)
	{
		close(STDIN_FILENO);
		if (dup(previous_fd) == -1)
			error = 1;
		close(previous_fd);
	}
	if (error == 1)
		return (-1);
	return (0);
}

int		execute_child_process(t_data *msh_data,
	t_cmd *cmd, int previous_fd, int pipefd[2])
{
	int	exit_status;

	if (child_file_handler(cmd->redirections[IN]->fd,
		previous_fd, pipefd[0]) == -1)
		return (-1);
	if (!cmd->is_last || cmd->redirections[OUT]->fd != STDOUT_FILENO)
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			return (-1);
	if (search_builtin(cmd->name))
	{
		exit_status = execute_builtin(msh_data, cmd);
		close(pipefd[1]);
		exit(exit_status);
	}
	else
		return (execute_child_process_execve(msh_data, cmd, pipefd));
}

int		execute_parent_process(t_data *msh_data,
	t_cmd *cmd, pid_t cpid, int pipefd[2])
{
	char	buf[BUFFER_SIZE];
	int		read_return;
	int		stat_loc;

	close(pipefd[1]);
	waitpid(cpid, &stat_loc, 0);
	if (WIFEXITED(stat_loc))
		msh_data->last_return = WEXITSTATUS(stat_loc);
	read_return = 1;
	if (cmd->redirections[OUT]->fd != STDOUT_FILENO)
	{
		while (read_return > 0)
		{
			read_return = read(pipefd[0], buf, BUFFER_SIZE);
			if (read_return == -1)
				return (-1);
			write(cmd->redirections[OUT]->fd, &buf, read_return);
		}
	}
	if (cmd->is_last)
	{
		close(pipefd[0]);
		return (EXIT_SUCCESS);
	}
	else
		return (pipefd[0]);
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

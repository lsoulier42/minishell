/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 01:11:17 by lsoulier          #+#    #+#             */
/*   Updated: 2021/01/13 01:11:25 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		execute_child_process_execve(t_data *msh_data,
	t_cmd *cmd, int pipefd[2])
{
	char	**envp;
	int		execve_return;
	char	*fullname;

	envp = serialize_env(msh_data->begin_env);
	if (!envp)
		return (-1);
	fullname = ft_strjoin(cmd->path, cmd->args[0]);
	if (!fullname)
		return (free_double_tab_ret_int(envp));
	execve_return = execve(fullname, cmd->args, envp);
	ft_double_tab_free(envp);
	close(pipefd[1]);
	if (execve_return == -1)
	{
		execve_error(fullname);
		free(fullname);
		if (errno == EACCES)
			exit(ACCESS_EXIT_STATUS);
		else
			exit(EXIT_FAILURE);
	}
	free(fullname);
	return (EXIT_SUCCESS);
}

int		child_file_handler(t_data *msh_data, int redir_in_fd,
	int previous_fd, int pipefd_read)
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
		return (ressource_error(msh_data, "dup", RESSOURCE_ERROR, -1));
	return (0);
}

int		execute_child_process(t_data *msh_data,
	t_cmd *cmd, int previous_fd, int pipefd[2])
{
	int	exit_status;

	if (child_file_handler(msh_data, cmd->redirections[IN]->fd,
		previous_fd, pipefd[0]) == -1)
		return (-1);
	if (!cmd->is_last || cmd->redirections[OUT]->fd != STDOUT_FILENO)
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			return (ressource_error(msh_data, "dup2", RESSOURCE_ERROR, -1));
	if (search_builtin(cmd->args[0]))
	{
		exit_status = execute_builtin(msh_data, cmd);
		close(pipefd[1]);
		exit(exit_status);
	}
	else
		return (execute_child_process_execve(msh_data, cmd, pipefd));
}

int		write_process_redirection(int read_fd, int out_fd)
{
	char	buf[BUFFER_SIZE];
	int		read_return;

	read_return = 1;
	while (read_return > 0)
	{
		read_return = read(read_fd, buf, BUFFER_SIZE);
		if (read_return == -1)
			return (0);
		write(out_fd, &buf, read_return);
	}
	return (1);
}

int		execute_parent_process(t_cmd *cmd, int pipefd[2])
{
	close(pipefd[1]);
	if (cmd->redirections[OUT]->fd != STDOUT_FILENO)
		if (!write_process_redirection(pipefd[0], cmd->redirections[OUT]->fd))
			return (-1);
	if (cmd->is_last)
	{
		close(pipefd[0]);
		return (EXIT_SUCCESS);
	}
	else
		return (pipefd[0]);
}

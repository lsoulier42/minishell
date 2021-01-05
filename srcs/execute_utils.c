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

int execute_child_process_execve(t_data *msh_data, t_cmd *cmd, int pipefd[2])
{
    char	**envp;

    envp = serialize_env(msh_data->begin_env);
    if (!envp)
        return (-1);
    execve(cmd->name, cmd->args, envp);
    ft_free_double_tab(envp);
    close(pipefd[1]);
    return (0);
}

int execute_child_process(t_data *msh_data, t_cmd *cmd, int previous_fd, int pipefd[2])
{
    close(pipefd[0]);
    if (cmd->redirections[IN]->fd != STDIN_FILENO)
    {
        close(STDIN_FILENO);
        dup(cmd->redirections[IN]->fd);
        close(cmd->redirections[IN]->fd);
    }
    else if (previous_fd != -1)
    {
        close(STDIN_FILENO);
        dup(previous_fd);
        close(previous_fd);
    }
    if (!cmd->is_last || cmd->redirections[OUT]->fd != STDOUT_FILENO)
        dup2(pipefd[1], STDOUT_FILENO);
    if (search_builtin(cmd->name))
    {
        execute_builtin(msh_data, cmd);
        close(pipefd[1]);
        exit(0);
    }
    else
        return (execute_child_process_execve(msh_data, cmd, pipefd));
}

int execute_parent_process(t_cmd *cmd, int pipefd[2])
{
    char    buf[BUFFER_SIZE];
    int     read_return;

    close(pipefd[1]);
    wait(NULL);
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
        return (0);
    }
    else
        return (pipefd[0]);
}

int execute_pipe_cmd(t_data *msh_data, t_cmd *cmd, int previous_fd)
{

    pid_t	cpid;
    int 	pipefd[2];

    if (pipe(pipefd) == -1)
        return (-1);
    cpid = fork();
    if (cpid == 0)
        return (execute_child_process(msh_data, cmd, previous_fd, pipefd));
    else if (cpid != -1)
        return (execute_parent_process(cmd, pipefd));
    return (-1);
}

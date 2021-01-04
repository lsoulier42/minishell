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

int execute_cmd(t_data *msh_data, t_cmd *cmd, int previous_fd, int is_last)
{
	char	**envp;
	pid_t	cpid;
	int 	pipefd[2];
	char    buf;

	if (pipe(pipefd) == -1)
		return (-1);
	cpid = fork();
	if (cpid == 0)
	{
		envp = serialize_env(msh_data->begin_env);
		if (!envp)
			return (-1);
		close(pipefd[0]);
		if (cmd->redirections[IN]->fd != STDIN_FILENO)
        {
		    close(STDIN_FILENO);
		    dup(cmd->redirections[IN]->fd);
		    close(cmd->redirections[IN]->fd);
        }
        if (previous_fd != -1)
        {
            close(STDIN_FILENO);
            dup(previous_fd);
            close(previous_fd);
        }
        if (!is_last || cmd->redirections[OUT]->fd != STDOUT_FILENO)
            dup2(pipefd[1], STDOUT_FILENO);
        if (search_builtin(cmd->name))
            execute_builtin(msh_data, cmd);
        else
		    execve(cmd->name, cmd->args, envp);
		close(pipefd[1]);
		free_double_tab(envp);
		return (0);
	}
	else if (cpid != -1)
	{
		close(pipefd[1]);
        wait(NULL);
        if (cmd->redirections[OUT]->fd != STDOUT_FILENO)
            while (read(pipefd[0], &buf, 1) > 0)
                write(cmd->redirections[OUT]->fd, &buf, 1);
		if (is_last) {
            close(pipefd[0]);
            return (0);
        }
		else {
            return (pipefd[0]);
        }
	}
	return (-1);
}

int	execute_all_cmds(t_data *msh_data)
{
	t_list	*instructions;
	t_list	*pipes;
	t_cmd	*cmd;
	int 	fdstdin;

	instructions = msh_data->parsed_input->begin_instructions;
	fdstdin = -1;
	while (instructions)
	{
		pipes = get_instruction_pipes(instructions);
		while (pipes)
		{
			cmd = get_cmd(pipes);
			if (!open_redirections(&(cmd->redirections)))
			    return (0);
			if (!expand_vars(msh_data, cmd))
				return (0);
            cmd->name = search_path(msh_data->begin_env, cmd->name);
            if (cmd->name != NULL)
                fdstdin = execute_cmd(msh_data, cmd, fdstdin, !(pipes->next));
            else
                format_error("minishell", cmd->name, 0, "Command not found");
			close_redirections(cmd->redirections);
			pipes = pipes->next;
		}
		instructions = instructions->next;
	}
	return (1);
}

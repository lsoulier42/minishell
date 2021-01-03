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



int execute_cmd(t_data *msh_data, char *full_path, t_cmd *cmd)
{
	char	**envp;
	pid_t	cpid;
	int 	pipefd[2];

	if (pipe(pipefd) == -1)
		return (-1);
	cpid = fork();
	if (cpid == 0)
	{
		envp = serialize_env(msh_data->begin_env);
		if (!envp)
			return (-1);
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		execve(full_path, cmd->args, envp);
		close(pipefd[1]);
		free_double_tab(envp);
		return (0);
	}
	else if (cpid != -1)
	{
		close(pipefd[1]);
		wait(NULL);
		return (pipefd[0]);
	}
	return (-1);
}

int	execute_all_cmds(t_data *msh_data)
{
	t_list	*instructions;
	t_list	*pipes;
	t_cmd	*cmd;
	char 	*full_path;
	int 	fdstdin;
	char 	buf;

	instructions = msh_data->parsed_input->begin_instructions;
	fdstdin = -1;
	while (instructions)
	{
		pipes = get_instruction_pipes(instructions);
		while (pipes)
		{
			cmd = get_cmd(pipes);
			open_redirections(&(cmd->redirections));
			if (!expand_vars(msh_data, cmd))
				return (0);
			if (search_builtin(cmd->name))
				execute_builtin(msh_data, cmd);
			else
			{
				full_path = search_path(msh_data->begin_env, cmd->name);
				if (full_path != NULL)
				{
					fdstdin = execute_cmd(msh_data, full_path, cmd);
					ft_putnbr(fdstdin);
					ft_putstr("\n");
				}
				else
					format_error("minishell", cmd->name, 0, "Command not found");
				free(full_path);
			}
			close_redirections(cmd->redirections);
			pipes = pipes->next;
		}
		instructions = instructions->next;
	}
	return (1);
}

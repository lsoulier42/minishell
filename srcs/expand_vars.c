/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 18:29:18 by lsoulier          #+#    #+#             */
/*   Updated: 2020/12/30 18:29:29 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_one_arg_vars(t_data msh_data, char **cur_arg)
{
	int	i;

	i = 0;
	while ((*cur_arg)[i])
	{
		if ((*cur_arg)[i] == '$' && (*cur_arg)[i + 1] != '\0'
			&& !ft_isspace((*cur_arg)[i + 1]) && (*cur_arg)[i + 1] != '$'
			&& (*cur_arg)[i + 1] != '?')
		{
			if (!expand_one_var(cur_arg, &i))
				return (0);
		}
		else if ((*cur_arg)[i] == '$' && (*cur_arg)[i + 1] == '?')
		{
			if (!expand_last_return(msh_data, cur_arg, &i))
				return (0);
		}
		else
			i++;
	}
	return (1);
}

int	expand_one_cmd_vars(t_data msh_data, t_cmd *cmd)
{
	int		i;

	i = 0;
	while (cmd->args[i])
	{
		if (!expand_one_arg_vars(msh_data, &(cmd->args[i])))
			return (0);
		i++;
	}
	return (1);
}

int	expand_vars(t_data msh_data)
{
	t_list	*instructions;
	t_list	*pipes;
	t_cmd	*cmd;

	instructions = msh_data.parsed_input->begin_instructions;
	while (instructions)
	{
		pipes = get_instruction_pipes(instructions);
		while (pipes)
		{
			cmd = get_cmd(pipes);
			if (!expand_one_cmd_vars(msh_data, cmd))
				return (0);
			pipes = pipes->next;
		}
		instructions = instructions->next;
	}
	return (1);
}

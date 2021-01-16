/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_input_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 02:46:35 by lsoulier          #+#    #+#             */
/*   Updated: 2020/12/29 02:46:41 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*error_tokens(t_user_input *new)
{
	free(new->input);
	free(new);
	return (NULL);
}

void	delete_token_list(t_list *pipes)
{
	t_list	*tokens;
	t_list	*tmp_tokens;

	if (pipes->content)
	{
		tokens = ((t_pipe *)(pipes->content))->begin_cmds;
		while (tokens)
		{
			tmp_tokens = tokens;
			free(get_token_value(tokens));
			free(tokens->content);
			tokens = tokens->next;
			free(tmp_tokens);
		}
	}
}

void	delete_pipes(t_list *instructions)
{
	t_list	*tmp_pipes;
	t_list	*pipes;

	pipes = get_instruction_pipes(instructions);
	while (pipes)
	{
		tmp_pipes = pipes;
		delete_token_list(pipes);
		if (pipes->content)
			free(pipes->content);
		pipes = pipes->next;
		free(tmp_pipes);
	}
}

void	*error_cmds(t_user_input *new, t_list *instructions)
{
	t_list	*tmp_instruction;

	while (instructions)
	{
		tmp_instruction = instructions;
		delete_pipes(instructions);
		if (instructions->content)
			free(instructions->content);
		instructions = instructions->next;
		free(tmp_instruction);
	}
	return (error_tokens(new));
}

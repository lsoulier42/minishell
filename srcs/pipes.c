/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 18:05:05 by lsoulier          #+#    #+#             */
/*   Updated: 2020/12/26 00:41:55 by louise           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

int			add_pipe(t_list **begin_pipes, t_list *begin_cmds)
{
	t_list	*el_pipe;

	el_pipe = new_pipe_el(begin_cmds, 0);
	if (!el_pipe)
		return (0);
	ft_lstadd_back(begin_pipes, el_pipe);
	return (1);
}

static int	parse_one_instruction_pipes(t_list *tokens, t_list **begin_pipes,
	t_list *previous, t_list *begin_cmds)
{
	while (tokens)
	{
		if ((token_is_pipe(tokens) || !tokens->next) && previous)
		{
			if (!add_pipe(begin_pipes, begin_cmds))
				return (0);
			begin_cmds = tokens->next;
			if (tokens->next)
			{
				previous->next = NULL;
				del_token_el(tokens);
			}
			tokens = begin_cmds;
		}
		else
		{
			previous = tokens;
			tokens = tokens->next;
		}
	}
	return (1);
}

int			parse_pipes(t_list *instructions)
{
	t_list	*tokens;
	t_list	**begin_pipes;
	t_list	*begin_cmds;
	t_list	*previous;

	while (instructions)
	{
		tokens = get_instruction_pipes(instructions);
		begin_pipes = &((t_instruction*)instructions->content)->begin_pipes;
		*begin_pipes = NULL;
		begin_cmds = tokens;
		previous = NULL;
		if (!parse_one_instruction_pipes(tokens, begin_pipes,
			previous, begin_cmds))
			return (0);
		instructions = instructions->next;
	}
	return (1);
}



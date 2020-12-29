/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 02:34:21 by lsoulier          #+#    #+#             */
/*   Updated: 2020/12/28 02:34:29 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int 	add_instruction(t_list **begin_instructions, t_list *begin_pipes)
{
	t_list	*el_instruction;

	el_instruction = new_instruction_el(begin_pipes, 0);
	if (!el_instruction)
		return (0);
	ft_lstadd_back(begin_instructions, el_instruction);
	return (1);
}

static int 	parse_instructions_loop(t_list **tokens,
	t_list **previous, t_list **begin_instructions, t_list **begin_pipes)
{
	if ((token_is_semicolon(*tokens) || !(*tokens)->next) && *previous)
	{
		if(!add_instruction(begin_instructions, *begin_pipes))
			return (0);
		*begin_pipes = (*tokens)->next;
		if ((*tokens)->next)
		{
			(*previous)->next = NULL;
			del_token_el(*tokens);
		}
		*tokens = *begin_pipes;
	}
	else
	{
		*previous = *tokens;
		*tokens = (*tokens)->next;
	}
	return (1);
}

t_list	*parse_instructions(t_list *tokens)
{
	t_list	*previous;
	t_list	*begin_instructions;
	t_list	*begin_pipes;

	begin_pipes = tokens;
	begin_instructions = NULL;
	previous = NULL;
	while (tokens)
		if (!parse_instructions_loop(&tokens, &previous, &begin_instructions, &begin_pipes))
			return (NULL);
	return (begin_instructions);
}

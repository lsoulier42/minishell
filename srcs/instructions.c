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

void			del_instruction(void *instruction_void)
{
	t_instruction *instruction;

	instruction = (t_instruction*)instruction_void;
	ft_lstclear(&instruction->begin_pipes, &del_pipe);
}

t_instruction	*new_instruction(t_list *begin_pipes, int exit_status)
{
	t_instruction *new;

	new = (t_instruction*)malloc(sizeof(t_instruction));
	if (!new)
		return (NULL);
	new->begin_pipes = begin_pipes;
	new->exit_status = exit_status;
	return (new);
}

t_list	*new_instruction_el(t_list *begin_pipes, int exit_status)
{
	t_list			*el;
	t_instruction	*new;

	new = new_instruction(begin_pipes, exit_status);
	if (!new)
		return (NULL);
	el = ft_lstnew(new);
	return (el);
}

int 	add_instruction(t_list **begin_instructions, t_list *begin_pipes_unparsed)
{
	t_list	*el_instruction;
	t_list	*begin_pipes;

	begin_pipes = parse_pipes(begin_pipes_unparsed);
	if (!begin_pipes)
		return (0);
	el_instruction = new_instruction_el(begin_pipes, 0);
	if (!el_instruction)
		return (0);
	ft_lstadd_back(begin_instructions, el_instruction);
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
	{
		if (token_is_semicolon(tokens) && previous)
		{
			if(!add_instruction(&begin_instructions, begin_pipes))
				return (NULL);
			begin_pipes = tokens->next;
			previous->next = NULL;
			del_token_el(tokens);
			tokens = begin_pipes;
		}
		else
		{
			previous = tokens;
			tokens = tokens->next;
		}
	}
	return (begin_instructions);
}

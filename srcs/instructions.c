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

	el_instruction = new_instruction_el(begin_pipes);
	if (!el_instruction)
		return (0);
	ft_lstadd_back(begin_instructions, el_instruction);
	return (1);
}

static int	pi_loop(t_list **to, t_list **pr, t_list **bi, t_list **bp)
{
	if (token_is_semicolon(*to) || !(*to)->next)
	{
		if (!add_instruction(bi, *bp))
			return (0);
		*bp = (*to)->next;
		if (token_is_semicolon(*to))
		{
			(*pr)->next = NULL;
			ft_lstdelone(*to, &del_token);
		}
		*to = *bp;
	}
	else
	{
		*pr = *to;
		*to = (*to)->next;
	}
	return (1);
}

void 	*del_instruction_list(t_list **begin_instructions)
{
	if (*begin_instructions)
		ft_lstclear(begin_instructions, &del_instruction);
	return (NULL);
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
		if (!pi_loop(&tokens, &previous,
				&begin_instructions, &begin_pipes))
			return (del_instruction_list(&begin_instructions));
	return (begin_instructions);
}

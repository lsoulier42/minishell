/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 16:36:55 by lsoulier          #+#    #+#             */
/*   Updated: 2020/12/28 16:38:29 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			del_instruction(void *instruction_void)
{
	t_instruction *instruction;

	instruction = (t_instruction*)instruction_void;
	ft_lstclear(&instruction->begin_pipes, &del_pipe);
	free(instruction_void);
}

t_instruction	*new_instruction(t_list *begin_pipes)
{
	t_instruction *new;

	new = (t_instruction*)malloc(sizeof(t_instruction));
	if (!new)
		return (NULL);
	new->begin_pipes = begin_pipes;
	return (new);
}

t_list			*new_instruction_el(t_list *begin_pipes)
{
	t_list			*el;
	t_instruction	*new;

	new = new_instruction(begin_pipes);
	if (!new)
		return (NULL);
	el = ft_lstnew(new);
	return (el);
}

t_list			*get_instruction_pipes(t_list *instruction_el)
{
	t_list	*el;
	t_instruction *instruction;

	instruction = (t_instruction*)instruction_el->content;
	el = (t_list*)instruction->begin_pipes;
	return (el);
}

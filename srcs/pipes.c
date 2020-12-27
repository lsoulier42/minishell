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

#include "minishell.c"

int 		is_pipe(t_instruction *it)
{
	if (!it)
		return (0);
	return(ft_strcmp(it->value, "|") == 0 && !it->is_quote);
}

t_pipe		*create_pipe(t_list *begin)
{
	t_instruction	*current;
	t_pipe			*new;
	t_list			*el;

	new = (t_pipe*)malloc(sizeof(t_pipe));
	if (!new)
		return (NULL);
	new->begin_cmd = NULL;
	while (begin)
	{
		current = (t_instruction*)begin->content;
		if (is_pipe(current))
			break ;
		el = ft_lstnew(current);
		if (!el)
			return (NULL);
		ft_lstadd_back(&new->begin_cmd, el);
		begin = begin->next;
	}
	return (new);
}

t_list		*split_pipes(t_list *instructions)
{
	t_list			*begin;
	t_list			*el;
	t_pipe			*new_pipe;
	t_instruction	*current;
	t_instruction	*previous;

	begin = NULL;
	previous = NULL;
	while (instructions)
	{
		current = (t_instruction*)instructions->content;
		if ((previous == NULL || is_pipe(previous)) && !is_pipe(current))
		{
			new_pipe = create_pipe(instructions);
			if (!new_pipe)
				return (NULL);
			el = ft_lstnew(new_pipe);
			if (!el)
				return (NULL);
			ft_lstadd_back(&begin, el);
		}
		previous = current;
		instructions = instructions->next;
	}
	return (begin);
}



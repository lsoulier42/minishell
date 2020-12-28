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

t_pipe	*new_pipe(t_list *begin_cmds, int exit_status)
{
	t_pipe *new;

	new = (t_pipe*)malloc(sizeof(t_pipe));
	if (!new)
		return (NULL);
	new->begin_cmds = begin_cmds;
	new->exit_status = exit_status;
	return (new);
}

t_list	*new_pipe_el(t_list *begin_cmds, int exit_status)
{
	t_pipe	*new;
	t_list	*el;

	new = new_pipe(begin_cmds, exit_status);
	if (!new)
		return (NULL);
	el = ft_lstnew(new);
	return (el);
}

void	del_pipe(void *pipe_void)
{
	t_pipe *pipe;

	pipe = (t_pipe*)pipe_void;
	ft_lstclear(&pipe->begin_cmds, &del_cmd);
}

int 	add_pipe(t_list **begin_pipes, t_list *begin_cmds_unparsed)
{
	t_list	*el_pipe;
	t_list	*begin_cmds;

	begin_cmds = parse_cmds(begin_cmds_unparsed);
	if (!begin_cmds)
		return (0);
	el_pipe = new_pipe_el(begin_cmds, 0);
	if (!el_pipe)
		return (0);
	ft_lstadd_back(begin_pipes, el_pipe);
	return (1);
}

t_list	*parse_pipes(t_list *tokens)
{
	t_list	*previous;
	t_list	*begin_pipes;
	t_list	*begin_cmds;

	begin_pipes = NULL;
	begin_cmds = tokens;
	previous = NULL;
	while (tokens)
	{
		if (token_is_pipe(tokens) && previous)
		{
			add_pipe(&begin_pipes, begin_cmds);
			begin_cmds = tokens->next;
			previous->next = NULL;
			del_token_el(tokens);
			tokens = begin_cmds;
		}
		else
		{
			previous = tokens;
			tokens = tokens->next;
		}
	}
	return (begin_pipes);
}

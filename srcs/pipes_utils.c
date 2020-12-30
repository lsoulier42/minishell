/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 01:10:21 by lsoulier          #+#    #+#             */
/*   Updated: 2020/12/29 01:10:31 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pipe	*new_pipe(t_list *begin_cmds)
{
	t_pipe *new;

	new = (t_pipe*)malloc(sizeof(t_pipe));
	if (!new)
		return (NULL);
	new->begin_cmds = begin_cmds;
	return (new);
}

t_list	*new_pipe_el(t_list *begin_cmds)
{
	t_pipe	*new;
	t_list	*el;

	new = new_pipe(begin_cmds);
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
	free(pipe_void);
}

t_list	*get_pipes_cmds(t_list *pipes_el)
{
	t_list	*el;
	t_pipe	*pipe;

	pipe = (t_pipe*)pipes_el->content;
	el = (t_list*)pipe->begin_cmds;
	return (el);
}

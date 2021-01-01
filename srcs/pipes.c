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

int	add_pipe(t_list **begin_pipes, t_list *begin_cmds)
{
	t_list	*el_pipe;

	el_pipe = new_pipe_el(begin_cmds);
	if (!el_pipe)
		return (0);
	ft_lstadd_back(begin_pipes, el_pipe);
	return (1);
}

static int	poip(t_list *to, t_list **bp, t_list *pr, t_list *bc)
{
	while (to)
	{
		if (token_is_pipe(to) || !to->next)
		{
			if (!add_pipe(bp, bc))
				return (0);
			bc = to->next;
			if (token_is_pipe(to))
			{
				pr->next = NULL;
				ft_lstdelone(to, &del_token);
			}
			to = bc;
		}
		else
		{
			pr = to;
			to = to->next;
		}
	}
	return (1);
}

int	del_pipe_list(t_list **begin_pipes)
{
	if (*begin_pipes)
		ft_lstclear(begin_pipes, &del_pipe);
	return (0);
}

int	parse_pipes(t_list *instructions)
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
		if (!poip(tokens, begin_pipes,
				previous, begin_cmds))
			return (del_pipe_list(begin_pipes));
		instructions = instructions->next;
	}
	return (1);
}

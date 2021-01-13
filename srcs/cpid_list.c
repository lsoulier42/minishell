/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpid_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 21:28:57 by lsoulier          #+#    #+#             */
/*   Updated: 2021/01/12 21:29:05 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cpid	*new_cpid(pid_t cpid)
{
	t_cpid	*new;

	new = (t_cpid*)malloc(sizeof(t_cpid));
	if (!new)
		return (NULL);
	new->child_pid = cpid;
	return (new);
}

t_list	*new_cpid_el(pid_t cpid)
{
	t_cpid	*new;
	t_list	*el;

	new = new_cpid(cpid);
	if (!new)
		return (NULL);
	el = ft_lstnew(new);
	if (!el)
		free(new);
	return (el);
}

int 	add_cpid(t_list **begin_cpid, pid_t cpid)
{
	t_list	*el;

	el = new_cpid_el(cpid);
	if (!el)
		return (0);
	ft_lstadd_front(begin_cpid, el);
	return (1);
}

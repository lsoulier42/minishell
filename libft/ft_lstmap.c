/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louise <lsoulier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 21:07:57 by louise            #+#    #+#             */
/*   Updated: 2020/10/09 22:29:45 by louise           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	lstclear(t_list **lst, void (*del)(void*))
{
	t_list *track;
	t_list *next;

	track = *lst;
	while (track)
	{
		next = track->next;
		track->next = NULL;
		(*del)(track->content);
		free(track);
		track = next;
	}
	*lst = NULL;
}

t_list		*ft_lstmap(t_list *lst, void *(*f)(void *),
		void (*del)(void *))
{
	t_list *begin;
	t_list *previous;
	t_list *new;

	begin = NULL;
	if (lst)
	{
		if (!(begin = ft_lstnew((*f)(lst->content))))
			return (NULL);
		previous = begin;
		lst = lst->next;
		while (lst)
		{
			if (!(new = ft_lstnew((*f)(lst->content))))
			{
				lstclear(&begin, del);
				return (NULL);
			}
			previous->next = new;
			previous = new;
			lst = lst->next;
		}
	}
	return (begin);
}

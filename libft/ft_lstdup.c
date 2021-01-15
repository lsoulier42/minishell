/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 15:11:37 by lsoulier          #+#    #+#             */
/*   Updated: 2021/01/15 15:11:43 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstdup(t_list *begin, void (*del)(void*))
{
	t_list	*el;
	t_list	*new;

	new = NULL;
	while (begin)
	{
		el = ft_lstnew(begin->content);
		if (new && !el)
		{
			ft_lstclear(&new, del);
			return (NULL);
		}
		ft_lstadd_back(&new, el);
		begin = begin->next;
	}
	return (new);
}

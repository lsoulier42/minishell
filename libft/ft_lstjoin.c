/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 21:15:34 by lsoulier          #+#    #+#             */
/*   Updated: 2021/01/09 21:15:42 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_lstjoin(t_list *begin)
{
	int		len;
	t_list	*track;
	char	*new;

	len = 0;
	track = begin;
	while (track)
	{
		len += ft_strlen((char*)track->content);
		track = track->next;
	}
	new = (char*)ft_calloc(len + 1, sizeof(char));
	if (!new)
		return (NULL);
	while (begin)
	{
		ft_strcat(new, (char*)begin->content);
		begin = begin->next;
	}
	return (new);
}

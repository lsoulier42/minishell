/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louise <lsoulier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 15:08:02 by louise            #+#    #+#             */
/*   Updated: 2020/10/09 22:00:01 by louise           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new;
	size_t	s_len;
	size_t	i;

	i = -1;
	if (s)
	{
		s_len = ft_strlen(s);
		if (!(new = (char*)malloc(sizeof(char) * (len + 1))))
			return (NULL);
		while (++i < len && start < s_len)
			new[i] = s[start + i];
		new[i] = '\0';
	}
	else
		new = NULL;
	return (new);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louise <lsoulier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 22:52:25 by louise            #+#    #+#             */
/*   Updated: 2020/09/21 14:45:21 by louise           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t i;
	size_t j;

	i = 0;
	if (!(*needle))
		return ((char*)haystack);
	while (haystack[i] && i < len)
	{
		if (haystack[i] == *needle)
		{
			j = 0;
			while (haystack[i + j] && needle[j] && (i + j) < len
					&& haystack[i + j] == needle[j])
				j++;
			if (!(needle[j]))
				return ((char*)(haystack + i));
		}
		i++;
	}
	return (NULL);
}

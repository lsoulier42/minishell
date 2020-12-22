/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louise <lsoulier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 19:35:48 by louise            #+#    #+#             */
/*   Updated: 2020/09/24 11:47:52 by louise           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		overlap_chr(void *dst, unsigned char *src, size_t len)
{
	size_t i;

	i = -1;
	while (++i < len)
		if (src + i == dst)
			return (1);
	return (0);
}

void			*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*src_uc;
	int				is_overlap;

	src_uc = (unsigned char*)src;
	i = -1;
	is_overlap = overlap_chr(dst, src_uc, len);
	if (dst || src)
	{
		if (!is_overlap)
			while (++i < len)
				*(unsigned char*)(dst + i) = src_uc[i];
		else
			while (++i < len)
				*(unsigned char*)(dst + len - i - 1) = src_uc[len - i - 1];
	}
	return (dst);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louise <lsoulier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 21:17:43 by louise            #+#    #+#             */
/*   Updated: 2020/09/24 11:38:20 by louise           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*s1_uc;
	unsigned char	*s2_uc;

	i = -1;
	s1_uc = (unsigned char*)s1;
	s2_uc = (unsigned char*)s2;
	while (++i < n)
		if (s1_uc[i] != s2_uc[i])
			return (s1_uc[i] - s2_uc[i]);
	return (!(*s1_uc) || !(*s2_uc) ? *s1_uc - *s2_uc : 0);
}

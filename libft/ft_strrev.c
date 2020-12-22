/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louise <lsoulier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 00:25:02 by louise            #+#    #+#             */
/*   Updated: 2020/09/28 00:29:40 by louise           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(const char *str)
{
	int		len;
	int		i;
	char	*rev;

	len = ft_strlen(str);
	i = -1;
	if (!(rev = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (++i < len)
		rev[i] = str[len - i - 1];
	rev[i] = '\0';
	return (rev);
}

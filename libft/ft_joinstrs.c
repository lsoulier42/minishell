/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_joinstrs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louise <lsoulier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 14:36:34 by louise            #+#    #+#             */
/*   Updated: 2020/09/28 14:43:27 by louise           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_char(int size, char **strs, char *sep)
{
	int i;
	int nb_char;

	i = -1;
	nb_char = size > 0 ? ft_strlen(sep) * (size - 1) : 0;
	while (++i < size)
		nb_char += ft_strlen(strs[i]);
	return (nb_char);
}

char		*ft_joinstrs(int size, char **strs, char *sep)
{
	int		i;
	char	*concat_str;
	int		nb_char;

	i = -1;
	nb_char = count_char(size, strs, sep);
	if (!(concat_str = malloc(sizeof(char) * (nb_char + 1))))
		return (NULL);
	*concat_str = '\0';
	while (++i < size)
	{
		concat_str = ft_strcat(concat_str, strs[i]);
		if (i < size - 1)
			concat_str = ft_strcat(concat_str, sep);
	}
	return (concat_str);
}

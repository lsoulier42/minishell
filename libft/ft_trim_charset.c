/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trim_charset.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 23:55:42 by lsoulier          #+#    #+#             */
/*   Updated: 2021/01/05 23:55:51 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_trim_charset(char *str, char *charset)
{
	char	*new_str;
	int		nb_char;
	int		i;
	int		j;
	int		k;

	i = -1;
	j = -1;
	k = 0;
	nb_char = 0;
	while (str[++i])
		if (ft_ischarset(str[i], charset))
			nb_char++;
	new_str = (char*)ft_calloc(ft_strlen(str) - nb_char + 1, sizeof(char));
	if (!new_str)
		return (NULL);
	while (str[++j])
		if (!ft_ischarset(str[j], charset))
			new_str[k++] = str[j];
	new_str[k] = '\0';
	return (new_str);
}

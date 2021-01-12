/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_merge_double_tab.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 11:31:33 by lsoulier          #+#    #+#             */
/*   Updated: 2021/01/12 11:31:43 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char **ft_double_tab_merge(char **tab1, char **tab2)
{
	char	**new;
	int		len;
	int		i;
	int		j;

	len = ft_double_tab_len(tab1) + ft_double_tab_len(tab2);
	new = (char**)malloc(sizeof(char*) * (len + 1));
	if (!new)
		return (NULL);
	i = -1;
	j = 0;
	while (tab1 && tab1[++i])
	{
		new[j] = ft_strdup(tab1[i]);
		if (!(new[j++]))
			return (ft_double_tab_free(new));
	}
	i = -1;
	while (tab2 && tab2[++i])
	{
		new[j] = ft_strdup(tab2[i]);
		if (!(new[j++]))
			return (ft_double_tab_free(new));
	}
	new[j] = NULL;
	return (new);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 03:25:17 by lsoulier          #+#    #+#             */
/*   Updated: 2020/12/31 03:25:24 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*parse_var_key(char *unparsed)
{
	char	*key;
	int		i;

	i = 0;
	while (unparsed[i] && unparsed[i] != '=')
		i++;
	if (unparsed[i] != '=')
		return (NULL);
	key = ft_strndup(unparsed, i);
	return (key);
}

char	*parse_var_value(char *unparsed)
{
	char	*value;
	int		i;
	int		len;

	i = 0;
	while (unparsed[i] && unparsed[i] != '=')
		i++;
	if (unparsed[i] != '=')
		return (NULL);
	len = ft_strlen(unparsed) - i - 1;
	value = (char*)malloc(sizeof(char) * (len + 1));
	if (!value)
		return (NULL);
	ft_strlcpy(value, unparsed + i + 1, len + 1);
	return (value);
}

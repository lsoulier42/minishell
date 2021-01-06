/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 04:21:57 by lsoulier          #+#    #+#             */
/*   Updated: 2020/12/29 04:22:05 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_isquote(char c)
{
	return (c == '"' || c == '\'');
}

int		len_to_first_quote(char *str)
{
	int i;

	i = 0;
	if (str)
		while (str[i] && (!ft_isquote(str[i])
			|| (i != 0 && str[i - 1] == '\\')))
			i++;
	return (i);
}

int		count_escaped_char(char *str, char quote_char)
{
	int i;
	int nb_char;

	i = -1;
	nb_char = 0;
	while (str[++i])
		if (str[i] == '\\' && !is_escaped(str, i))
			nb_char++;
	return (nb_char);
}

int		is_escaped(char *str, int char_index)
{
	if (char_index == 0)
		return (0);
	if (str[char_index - 1] == '\\')
		return (is_escaped(str, char_index - 1) == 0);
	return (0);
}

char	*sub_quote(char *str)
{
	int		first_quote;
	char	*new_str;
	int		i;
	int		j;

	i = -1;
	j = 0;
	first_quote = len_to_first_quote(str);
	new_str = (char*)ft_calloc(ft_strlen(str)
		- count_escaped_char(str, str[first_quote]) - 1, sizeof(char));
	if (!new_str)
		return (NULL);
	while (str[++i])
	{
		if ((str[i] != str[first_quote] || is_escaped(str, i))
			&& (str[i] != '\\' || is_escaped(str, i)))
			new_str[j++] = str[i];
	}
	new_str[j] = '\0';
	return (new_str);
}

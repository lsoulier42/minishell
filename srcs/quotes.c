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

/*int		len_to_first_quote(char *str)
{
	int i;

	i = 0;
	if (str)
		while (str[i] && (!ft_isquote(str[i])
			|| (i != 0 && str[i - 1] == '\\')))
			i++;
	return (i);
}

int		is_weakquote_specchar(char c)
{
	return (c == '$' || c == '`' || c == '"' || c == '\n');
}

int 	is_printable_quote(char *str, int i, char quote_char)
{
	return ((quote_char == '\'' && str[i] != quote_char)
		|| (quote_char == '"' && ((str[i] != quote_char && str[i] != '\\')
		|| (str[i] == quote_char && is_escaped(str, i))
		|| (str[i] == '\\' && str[i + 1] != '\\'
		&& !is_weakquote_spec_char(str[i + 1])))));
}

char	*sub_quote(char *str)
{
	char	*new_str;
	int		i;
	int		j;
	char 	quote_char;

	i = -1;
	j = 0;
	quote_char = str[len_to_first_quote(str)];
	if (quote_char == '\0')
		return (trail_backslash(str));
	new_str = (char*)ft_calloc(ft_strlen(str)
		- count_escaped_char_quotes(str, quote_char) - 1, sizeof(char));
	if (!new_str)
		return (NULL);
	while (str[++i])
	{
		if (is_printable_quote(str, i, quote_char))
			new_str[j++] = str[i];
		else if (quote_char == '"' && str[i] == '\\' && str[i + 1] == '\\')
			new_str[j++] = str[i++];
	}
	new_str[j] = '\0';
	return (new_str);
}
*/
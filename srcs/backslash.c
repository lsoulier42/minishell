/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backslash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 17:11:44 by lsoulier          #+#    #+#             */
/*   Updated: 2021/01/07 17:11:58 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_escaped(char *str, int char_index)
{
	if (char_index == 0)
		return (0);
	if (str[char_index - 1] == '\\')
		return (is_escaped(str, char_index - 1) == 0);
	return (0);
}

/*int 	is_specchar(char c)
{
	return (ft_isseparator(c) || c == '#' || c == '$');
}

int		count_escaped_char_quotes(char *str, char quote_char)
{
	int i;
	int nb_char;

	i = -1;
	if (quote_char == '\'')
		return (0);
	nb_char = 0;
	while (str[++i])
	{
		if (str[i] == '\\' && is_weakquote_spec_char(str[i + 1]))
			nb_char++;
		else if (str[i] == '\\' && str[i + 1] == '\\')
		{
			nb_char++;
			i++;
		}
	}
	return (nb_char);
}

int 	count_escaped_char(char *str)
{
	int i;
	int nb_char;

	i= -1;
	nb_char = 0;
	while(str[++i])
		if (str[i] == '\\' && !is_escaped(str, i) && !ft_isseparator(str[i + 1]))
			nb_char ++;
	return (nb_char);
}

char	*trail_backslash(char *str)
{
	int		i;
	int 	j;
	char	*trail_str;
	int 	new_len;

	new_len = ft_strlen(str) - count_escaped_char(str);
	trail_str = (char*)malloc(sizeof(char) * (new_len + 1));
	if (!trail_str)
		return (NULL);
	i = -1;
	j = 0;
	while (str[++i])
		if (str[i] != '\\' || (str[i] == '\\' && !is_escaped(str, i) && !ft_isseparator(str[i + 1])))
			trail_str[j++] = str[i];
	return (trail_str);
}*/

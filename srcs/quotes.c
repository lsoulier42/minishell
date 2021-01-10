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

char expand_set_quote_char(char quote_char, char *arg, int i)
{
	if (!quote_char && ft_isquote(arg[i]) && !is_escaped(arg, i))
		quote_char = arg[i];
	else if ((quote_char == '\'' && arg[i] == '\'')
			 || (quote_char == '"' && arg[i] == '"' && !is_escaped(arg, i)))
		quote_char = '\0';
	return (quote_char);
}

int expand_is_printable(char *arg, int i, char quote_char)
{
	return ((!ft_isquote(arg[i]) && arg[i] != '\\' && arg[i] != '$')
			|| (arg[i] == '$'
				&& !ft_isalnum(arg[i + 1])
				&& arg[i + 1] != '_' && arg[i + 1] != '?')
			|| (quote_char == '\'' && arg[i] != quote_char)
			|| (quote_char == '"' && arg[i] == quote_char && is_escaped(arg, i))
			|| (quote_char == '"' && arg[i] == '\'')
			|| (quote_char == '"' && arg[i] == '\\'
				&& (!is_weakquote_specchar(arg[i + 1]) || is_escaped(arg, i)))
			|| (quote_char == '\0' && arg[i] == '\\'
				&& (is_escaped(arg, i) || !is_specchar(arg[i + 1])))
			|| (quote_char != '\'' && arg[i] == '$' && is_escaped(arg, i)));
}

int expand_is_expandable_var(char *arg, int i, char quote_char)
{
	return (quote_char != '\'' && arg[i] == '$' && !is_escaped(arg, i)
			&& (ft_isalnum(arg[i + 1]) || arg[i + 1] == '_'));
}

int expand_is_last_return_var(char *arg, int i, char quote_char)
{
	return (quote_char != '\'' && arg[i] == '$'
			&& !is_escaped(arg, i) && arg[i + 1] == '?');
}


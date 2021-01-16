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

int		is_weakquote_specchar(char c)
{
	return (c == '$' || c == '`'
		|| c == '"' || c == '\n' || c == '\\');
}

int		is_specchar(char c)
{
	return (ft_isseparator(c) || ft_isquote(c) || c == '`'
		|| c == '#' || c == '$' || c == '\\');
}

int		expand_is_flushable_buffer(char *arg, int i, int j, char quote_char)
{
	return (j == BUFFER_SIZE || expand_is_expandable_var(arg, i, quote_char)
			|| expand_is_last_return_var(arg, i, quote_char));
}

void	expand_init_var(int *i, int *j, char *quote_char, t_list **begin)
{
	*quote_char = '\0';
	*i = -1;
	*j = 0;
	*begin = NULL;
}

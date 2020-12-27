/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 11:01:06 by lsoulier          #+#    #+#             */
/*   Updated: 2020/12/27 14:33:45 by louise           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int 	quote_char(char c)
{
	return (c == '\'' || c == '\"');
}

int		count_quote_len(char *str, char quote_c)
{
	int len;

	len = 0;
	while (str[len] && str[len] != quote_c)
		len++;
	if (str[len] != quote_c)
		return (-1);
	return (len);
}

int				add_instruct_quote(t_list **begin, char **str)
{
	t_list	*el;
	char 	*new;
	int 	quote_len;

	quote_len = count_quote_len(*str, **str);
	if (quote_len == -1)
		return (0);
	new = (char*)malloc(sizeof(char) * (quote_len + 1));
	if (!new)
		return (0);
	ft_strlcpy(new, *str, quote_len + 1);
	el = create_instruction_el(new, 1);
	if (!el)
	{
		free(new);
		return (0);
	}
	ft_lstadd_back(begin, el);
	*str += quote_len + 1;
	return (1);
}

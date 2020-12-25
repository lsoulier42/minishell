/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 11:01:06 by lsoulier          #+#    #+#             */
/*   Updated: 2020/12/25 19:29:50 by louise           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int 	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

int 	quote_len(char *input, int start)
{
	int		len;

	len = 0;
	while (input[start + len + 1] && input[start + len + 1] != input[start])
		len++;
	if (input[start + len + 1] != input[start])
		return (-1);
	return (len);
}

int		create_quote(char *input, int start, int len, t_list **begin)
{
	t_list	*el;
	char 	*new_str;

	new_str = ft_substr(input, start + 1, len);
	if (!new_str)
		return (0);
	el = ft_lstnew(new_str);
	if (!el)
	{
		free(new_str);
		return (0);
	}
	ft_lstadd_back(begin, el);
	return (1);
}

t_list	*parse_quotes(char **input)
{
	t_list	*begin;
	int 	new_len;
	int 	q_len;
	int 	i;

	i = -1;
	begin = NULL;
	while (*input[++i])
	{
		if (is_quote(*input[i]))
		{
			q_len = quote_len(*input, i);
			if (q_len == -1)
				return (NULL);//protection pour la quote n'est pas fermee
			if (!create_quote(*input, i, q_len, &begin))
				return (NULL);
			new_len = ft_strlen(*input) - q_len - i - 1; //la taille de la chaine moins la taille de la quote, mais comme on commence a copier depuis le caractere apres la premiere quote, on retire la taille de la chaine avant la premiere quote, et pour la premiere quote
			ft_strlcpy(*input + i + 1, *input + i + q_len + 1, new_len + 1);
			i += 2;//puisqu'on saute les 2 quotes
		}
	}
	return (begin);
}

char	*expand_quote(t_list *quotes, int index)
{
	char	*str;
	t_list	*el;

	el = ft_lstat(quotes, index);
	str = (char*)el->content;
	return (str);
}

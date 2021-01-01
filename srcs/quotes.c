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

int	ft_isquote(char c)
{
	return (c == '"' || c == '\'');
}

char	*sub_quote(char *str)
{
	int		first_quote;
	int		second_quote;
	char	*new_str;

	first_quote = 0;
	second_quote = 1;
	while (str[first_quote] && !ft_isquote(str[first_quote]))
		first_quote++;
	if (!str[first_quote])
		return (ft_strdup(str));
	while (str[first_quote + second_quote]
		   && str[first_quote + second_quote] != str[first_quote])
		second_quote++;
	new_str = (char*)ft_calloc(ft_strlen(str) - 1, sizeof(char));
	if (new_str)
	{
		ft_strlcpy(new_str, str, first_quote + 1);
		ft_strlcat(new_str,
			 str + first_quote + 1, first_quote + second_quote);
		ft_strlcat(new_str,
			 str + first_quote + second_quote + 1, ft_strlen(str) - 1);
	}
	return (new_str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 20:53:18 by lsoulier          #+#    #+#             */
/*   Updated: 2020/12/27 20:53:27 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*double_tab_to_tokens(char **tab)
{
	int		i;
	t_list	*begin;
	t_list	*token;
	char	*value;

	i = -1;
	begin = NULL;
	while (tab[++i])
	{
		value = ft_strdup(tab[i]);
		if (!value)
			return (NULL);
		token = new_token_el(value, 0);
		if (begin && !token)
		{
			ft_lstclear(&begin, &del_token);
			return (free_return_null(value));
		}
		ft_lstadd_back(&begin, token);
	}
	return (begin);
}

int		token_is_operator(t_list *el)
{
	t_token	*token;

	token = (t_token*)el->content;
	return (token->is_operator);
}

int		token_is_pipe(t_list *el)
{
	t_token	*token;

	token = (t_token*)el->content;
	return (token->is_operator && ft_strcmp("|", token->value) == 0);
}

int		token_is_semicolon(t_list *el)
{
	t_token	*token;

	token = (t_token*)el->content;
	return (token->is_operator && ft_strcmp(";", token->value) == 0);
}

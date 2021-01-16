/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 20:53:01 by lsoulier          #+#    #+#             */
/*   Updated: 2020/12/27 20:53:10 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*new_token(char *value, int is_operator)
{
	t_token	*new;

	new = (t_token*)malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->value = value;
	new->is_operator = is_operator;
	return (new);
}

void	del_token(void *token_void)
{
	t_token	*token;

	token = (t_token *)token_void;
	free(token->value);
	free(token_void);
}

t_list	*new_token_el(char *value, int is_operator)
{
	t_list	*el;
	t_token	*token;

	token = new_token(value, is_operator);
	if (!token)
		return (NULL);
	el = ft_lstnew(token);
	if (!el)
	{
		del_token(token);
		return (NULL);
	}
	return (el);
}

char	*get_token_value(t_list *el)
{
	t_token	*token;

	token = (t_token*)el->content;
	return (token->value);
}

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

int	ft_isoperator(char c)
{
	return (c == '|' || c == ';' || c == '>' || c == '<');
}

int	ft_isseparator(char c)
{
	return (ft_isspace(c) || ft_isoperator(c));
}

int	token_is_operator(t_list *el)
{
	t_token	*token;

	token = (t_token*)el->content;
	return (token->is_operator);
}

int	token_is_pipe(t_list *el)
{
	t_token	*token;

	token = (t_token*)el->content;
	return (token->is_operator && ft_strcmp("|", token->value) == 0);
}

int	token_is_semicolon(t_list *el)
{
	t_token	*token;

	token = (t_token*)el->content;
	return (token->is_operator && ft_strcmp(";", token->value) == 0);
}

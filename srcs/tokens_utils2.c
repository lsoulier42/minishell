/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 20:59:19 by lsoulier          #+#    #+#             */
/*   Updated: 2020/12/27 20:59:28 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*split_tokens(char *user_input)
{
	t_list	*begin;
	char	*input;
	char	*tmp;

	begin = NULL;
	input = ft_strdup(user_input);
	if (!input)
		return (NULL);
	tmp = input;
	while (*input)
	{
		if (!ft_isspace(*input))
		{
			if (!add_token(&begin, &input))
				return (free_token_struct(&begin, tmp));
		}
		else
			input += 1;
	}
	if (!check_token_list(begin))
		return (free_token_struct(&begin, tmp));
	free(tmp);
	return (begin);
}

char	*get_token_value(t_list *el)
{
	t_token	*token;

	token = (t_token*)el->content;
	return (token->value);
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

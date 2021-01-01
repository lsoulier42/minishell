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

	token = (t_token *) token_void;
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

int	add_token(t_list **begin, char **input)
{
	t_list	*el;
	char	*value;
	int		len;

	if (ft_isoperator(**input))
		len = token_len_operator(*input);
	else
		len = token_len(*input);
	if (len == -1)
		return (error_lexer(**input));
	value = ft_strndup(*input, len);
	if (!value)
		return (0);
	el = new_token_el(value, ft_isoperator(**input));
	if (!el)
		return (free_return_int(value));
	ft_lstadd_back(begin, el);
	*input += len;
	return (1);
}

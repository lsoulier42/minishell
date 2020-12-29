/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 01:39:04 by lsoulier          #+#    #+#             */
/*   Updated: 2020/12/29 01:39:12 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int 	error_operator_is_last_token(void)
{
	ft_putstr("syntax error near unexpected token `newline'\n");
	return (0);
}

int 	error_quote_is_not_closed(void)
{
	ft_putstr("syntax error quote is not closed\n");
	return (0);
}

int		check_token_list(t_list *tokens)
{
	char *value;

	while (tokens)
	{
		value = get_token_value(tokens);
		if (token_is_operator(tokens) && (ft_strcmp(value, "|") == 0
										  || ft_strcmp(value, ">") == 0
										  || ft_strcmp(value, "<") == 0
										  || ft_strcmp(value, ">>") == 0))
		{
			if (!tokens->next)
				return (error_operator_is_last_token());
			if (token_is_operator(tokens->next))
				return (error_operator_is_last_token());
		}
		tokens= tokens->next;
	}
	return (1);
}

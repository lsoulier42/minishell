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

int	error_operator_is_last_token(void)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putendl_fd("syntax error near unexpected token `newline'", STDERR_FILENO);
	return (0);
}

int	error_quote_is_not_closed(void)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putendl_fd("syntax error : quote is not closed", STDERR_FILENO);
	return (0);
}

int	error_operator_defined(void)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putendl_fd("syntax error : operator is not defined", STDERR_FILENO);
	return (0);
}

int	error_lexer(char c)
{
	if (ft_isoperator(c))
		return (error_operator_defined());
	else
		return (error_quote_is_not_closed());
}

int	check_token_list(t_list *tokens)
{
	char	*value;
	int		i;

	i = 0;
	while (tokens)
	{
		value = get_token_value(tokens);
		if (i++ == 0 && token_is_operator(tokens))
			return (error_operator_is_last_token());
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
		tokens = tokens->next;
	}
	return (1);
}

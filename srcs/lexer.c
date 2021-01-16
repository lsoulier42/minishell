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

t_list	*lexer(char *input, int bypass)
{
	t_list	*begin;

	begin = NULL;
	while (*input && *input != '#')
	{
		if (!ft_isspace(*input))
		{
			if (!add_token(&begin, &input))
			{
				ft_lstclear(&begin, &del_token);
				return (NULL);
			}
		}
		else
			input++;
	}
	if (!check_token_list(begin, bypass))
	{
		ft_lstclear(&begin, &del_token);
		return (NULL);
	}
	return (begin);
}

int		token_len_operator(char *input)
{
	int	len;

	len = 1;
	if (*input == '>' && *(input + 1) == '>')
		len = 2;
	else if (ft_isoperator(*(input + 1)))
		return (-1);
	return (len);
}

int		token_len(char *input)
{
	int		len;
	int		open;
	char	open_char;

	open = 0;
	len = 0;
	while (input[len] && (!ft_isseparator(input[len]) || open))
	{
		if (!open && ft_isquote(input[len]) && !is_escaped(input, len))
		{
			open = 1;
			open_char = input[len];
		}
		else if (open && input[len] == open_char && (open_char == '\''
			|| (open_char == '"' && !is_escaped(input, len))))
			open = 0;
		if (!open && (input[len] == '\\' && !is_escaped(input, len)))
			len++;
		if (input[len])
			len++;
	}
	if (open)
		return (-1);
	return (len);
}

int		add_token(t_list **begin, char **input)
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

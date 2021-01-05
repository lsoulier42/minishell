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

int	token_len_operator(char *input)
{
	int	len;

	len = 1;
	if (*input == '>' && *(input + 1) == '>')
		len = 2;
	else if (ft_isoperator(*(input + 1)))
		return (-1);
	return (len);
}

int	token_len(char *input)
{
	int		len;
	int		open;
	char	open_char;

	open = 0;
	len = 0;
	while (input[len] && (!ft_isseparator(input[len]) || open))
	{
		if (!open && (input[len] == '"' || input[len] == '\''))
		{
			open = 1;
			open_char = input[len];
		}
		else if (open && input[len] == open_char)
			open = 0;
		len++;
	}
	if (open)
		return (-1);
	return (len);
}

void	*free_token_struct(t_list **begin, char *tmp)
{
	ft_lstclear(begin, &del_token);
	free(tmp);
	return (NULL);
}

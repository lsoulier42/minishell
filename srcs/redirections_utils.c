/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 01:57:48 by lsoulier          #+#    #+#             */
/*   Updated: 2020/12/30 01:58:20 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redirection	*new_redirection(int fd)
{
	t_redirection	*new;

	new = (t_redirection*)malloc(sizeof(t_redirection));
	if (!new)
		return (NULL);
	new->fd = fd;
	return (new);
}

int				token_is_redirection(t_list *token_el)
{
	char	*value;

	if (!token_el->next)
		return (0);
	value = get_token_value(token_el);
	return (token_is_operator(token_el) && (ft_strcmp(value, ">") == 0
		|| ft_strcmp(value, "<") == 0 || ft_strcmp(value, ">>") == 0));
}

int				redirection_is_not_last(t_list *token_el)
{
	int direction;
	int cur_direction;

	direction = ft_strcmp(get_token_value(token_el), "<") == 0 ? IN : OUT;
	token_el = token_el->next;
	while (token_el)
	{
		if (token_is_redirection(token_el))
		{
			cur_direction = OUT;
			if (ft_strcmp(get_token_value(token_el), "<") == 0)
				cur_direction = IN;
			if (cur_direction == direction)
				return (1);
		}
		token_el = token_el->next;
	}
	return (0);
}

int				close_redirections(t_redirection **redirections)
{
	int i;

	i = -1;
	while (++i < 2)
		if (redirections[i]->fd > 2)
			close(redirections[i]->fd);
	return (1);
}

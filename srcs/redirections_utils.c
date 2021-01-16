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

void			del_redirection(void *redirection_void)
{
	t_redirection	*redirection;

	redirection = (t_redirection*)redirection_void;
	free(redirection->filename);
	free(redirection_void);
}

t_redirection	*new_redirection(char *filename, int fd, int type)
{
	t_redirection	*new;

	new = (t_redirection*)malloc(sizeof(t_redirection));
	if (!new)
		return (NULL);
	new->filename = filename;
	new->fd = fd;
	new->type = type;
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
	token_el = token_el->next;
	while (token_el)
	{
		if (token_is_redirection(token_el))
			return (1);
		token_el = token_el->next;
	}
	return (0);
}

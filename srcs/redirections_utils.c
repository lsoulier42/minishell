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

void	del_redirection(void *redirection_void)
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

int	token_is_redirection(t_list *token_el)
{
	char	*value;

	if (!token_el->next)
		return (0);
	value = get_token_value(token_el);
	return (token_is_operator(token_el) && (ft_strcmp(value, ">") == 0
				|| ft_strcmp(value, "<") == 0 || ft_strcmp(value, ">>") == 0));
}

int	redirection_is_not_last(t_list *token_el)
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

int	create_empty_file_redirection(char *filename, int type)
{
	int	fd;
	int	close_return;

	if (type == APPEND)
		fd = open(filename, O_RDWR | O_CREAT | O_APPEND, 0664);
	else
		fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0664);
	if (fd == -1)
		return (0);
	close_return = close(fd);
	if (close_return == -1)
		return (0);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_files.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 20:45:04 by lsoulier          #+#    #+#             */
/*   Updated: 2021/01/03 20:45:15 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	close_redirections(t_redirection **redirections)
{
	int i;

	i = -1;
	while (++i < 2)
		if (redirections[i]->filename != NULL)
			if (close(redirections[i]->fd) == -1)
				return (0);
	return (1);
}

int open_redirections(t_redirection ***redirections)
{
	int		i;
	int		fd;
	int		type;

	i = -1;
	while (++i < 2)
	{
		if ((*redirections)[i]->filename != NULL)
		{
			type = O_TRUNC;
			if ((*redirections)[i]->type == APPEND)
				type = O_APPEND;
			fd = open((*redirections)[i]->filename, O_RDWR | O_CREAT | type, 0664);
			if (fd == -1)
				return (0);
			(*redirections)[i]->fd = fd;
		}
	}
	return (1);
}

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
			close(redirections[i]->fd);
	return (1);
}

int open_redirections(t_redirection ***redirections)
{
	int		fd;
	int		type;

    if ((*redirections)[OUT]->filename != NULL)
    {
        type = O_TRUNC;
        if ((*redirections)[OUT]->type == APPEND)
            type = O_APPEND;
        fd = open((*redirections)[OUT]->filename, O_RDWR | O_CREAT | type, 0664);
        if (fd == -1)
            return (0);
        (*redirections)[OUT]->fd = fd;
    }
	if ((*redirections)[IN]->filename != NULL)
    {
	    fd = open((*redirections)[IN]->filename, O_RDONLY);
	    if (fd == -1)
	        return (0);
        (*redirections)[IN]->fd = fd;
    }
	return (1);
}

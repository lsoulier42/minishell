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

int		close_redirections(t_redirection **redirections)
{
	int i;

	i = -1;
	while (++i < 2)
		if (redirections[i]->filename != NULL)
			close(redirections[i]->fd);
	return (1);
}

int		open_redirection_out(t_redirection **redirection)
{
	int type;
	int fd;

	type = O_TRUNC;
	if ((*redirection)->type == APPEND)
		type = O_APPEND;
	fd = open((*redirection)->filename,
			  O_RDWR | O_CREAT | type, 0664);
	if (fd == -1)
	{
		open_file_error((*redirection)->filename);
		return (0);
	}
	(*redirection)->fd = fd;
	return (1);
}

int 	open_redirection_in(t_redirection **redirection)
{
	int fd;

	fd = open((*redirection)->filename, O_RDONLY);
	if (fd == -1)
	{
		open_file_error((*redirection)->filename);
		return (0);
	}
	(*redirection)->fd = fd;
	return (1);
}

int		open_redirections(t_redirection ***redirections)
{
	int	error;

	error = 0;
	if ((*redirections)[OUT]->filename != NULL)
		if (!open_redirection_out(&((*redirections)[OUT])))
			error = 1;
	if ((*redirections)[IN]->filename != NULL)
		if (!open_redirection_in(&((*redirections)[IN])))
			error = 1;
	return (error == 0);
}

int				create_empty_file_redirection(char *filename, int type)
{
	int	fd;

	if (type == APPEND)
		fd = open(filename, O_RDWR | O_CREAT | O_APPEND, 0664);
	else
		fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0664);
	if (fd == -1)
	{
		open_file_error(filename);
		return (0);
	}
	close(fd);
	return (1);
}

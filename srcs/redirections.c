/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 18:05:19 by lsoulier          #+#    #+#             */
/*   Updated: 2020/12/24 18:05:24 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		open_files(t_data *msh_data, int direction,
	char *filename, int type_open)
{
	int		fd;

	if (arg_is_var_alone(filename))
		filename = get_env_var(msh_data->begin_env, filename + 1)->value;
	if (direction == OUT)
	{
		fd = open(filename, O_RDWR | O_CREAT | type_open, 0664);
		if (fd == -1)
			open_file_error(filename);
	}
	else
	{
		fd = open(filename, O_RDONLY);
		if (fd == -1)
			open_file_error(filename);
	}
	return (fd);
}

int		parse_one_redirection(t_data *msh_data, t_list *tokens,
	int redirections[][2])
{
	int		type_open;
	int		direction;
	int		fd;
	int		is_not_last;
	char	*filename;

	is_not_last = redirection_is_not_last(tokens);
	direction = OUT;
	if (ft_strcmp(get_token_value(tokens), "<") == 0)
		direction = IN;
	type_open = O_TRUNC;
	if (ft_strcmp(get_token_value(tokens), ">>") == 0)
		type_open = O_APPEND;
	filename = get_token_value(tokens->next);
	fd = open_files(msh_data, direction, filename, type_open);
	if (fd == -1)
		return (0);
	if (!is_not_last)
		(*redirections)[direction] = fd;
	else
		close(fd);
	return (1);
}

void	delete_redirection_tokens(t_list **begins_cmds, t_list *token)
{
	t_list *track;
	t_list *previous;
	t_list *next;

	track = *begins_cmds;
	previous = NULL;
	while (track)
	{
		if (track == token)
		{
			next = token->next->next;
			ft_lstdelone(token->next, &del_token);
			ft_lstdelone(token, &del_token);
			if (previous)
				previous->next = next;
			else
				*begins_cmds = next;
			break ;
		}
		previous = track;
		track = track->next;
	}
}

int		parse_redirections(t_data *msh_data,
	t_list **begin_cmds, int redirections[][2])
{
	t_list	*tokens;
	t_list	*next;

	tokens = *begin_cmds;
	while (tokens)
	{
		if (token_is_redirection(tokens))
		{
			if (!parse_one_redirection(msh_data, tokens, redirections))
				return (0);
			next = tokens->next->next;
			delete_redirection_tokens(begin_cmds, tokens);
			tokens = next;
		}
		else
			tokens = tokens->next;
	}
	return (1);
}

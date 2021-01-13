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

int				parse_one_redirection(t_list *tokens,
	t_redirection ***redirections)
{
	char	*value;
	char	*filename;
	int		type_open;
	int		direction;

	value = get_token_value(tokens);
	filename = ft_strdup(get_token_value(tokens->next));
	if (!filename)
		return (0);
	direction = IN;
	if (ft_strcmp(value, ">>") == 0 || ft_strcmp(value, ">") == 0)
		direction = OUT;
	type_open = TRUNCATE;
	if (ft_strcmp(value, ">>") == 0)
		type_open = APPEND;
	if (redirection_is_not_last(tokens) && direction == OUT)
	{
		if (!create_empty_file_redirection(filename, type_open))
			return (free_return_int(filename));
		free(filename);
		return (1);
	}
	(*redirections)[direction]->filename = filename;
	(*redirections)[direction]->type = type_open;
	return (1);
}

void			delete_redirection_tokens(t_list **begins_cmds, t_list *token)
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

static int		parse_redirections_loop(t_list **begins_cmds,
	t_redirection ***redirections)
{
	t_list	*tokens;
	t_list	*next;

	tokens = *begins_cmds;
	while (tokens)
	{
		if (token_is_redirection(tokens))
		{
			if (!parse_one_redirection(tokens, redirections))
				return (0);
			next = tokens->next->next;
			delete_redirection_tokens(begins_cmds, tokens);
			tokens = next;
		}
		else
			tokens = tokens->next;
	}
	return (1);
}

t_redirection	**parse_redirections(t_list **begin_cmds)
{
	t_redirection	**redirections;

	redirections = (t_redirection**)malloc(sizeof(t_redirection*) * 2);
	if (!redirections)
		return (NULL);
	redirections[IN] = new_redirection(NULL, 0, APPEND);
	if (!redirections[IN])
		return (free_return_null(redirections));
	redirections[OUT] = new_redirection(NULL, 1, APPEND);
	if (!redirections[OUT])
	{
		free(redirections[IN]);
		return (free_return_null(redirections));
	}
	if (!parse_redirections_loop(begin_cmds, &redirections))
	{
		free(redirections[IN]);
		free(redirections[OUT]);
		return (free_return_null(redirections));
	}
	return (redirections);
}

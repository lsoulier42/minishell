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

int	parse_one_redirection(t_list *tokens, t_redirection ***redirections)
{
	char	*value;
	char	*filename;
	int		type_open;
	int 	direction;

	value = get_token_value(tokens);
	filename = sub_quote(get_token_value(tokens->next));
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
		return (1);
	}
	(*redirections)[direction]->filename = filename;
	(*redirections)[direction]->type = type_open;
	return (1);
}

void	delete_redirection_tokens(t_list **tokens, t_list **previous)
{
	t_list	*jump_token;

	jump_token = (*tokens)->next->next;
	ft_lstdelone((*tokens)->next, &del_token);
	ft_lstdelone(*tokens, &del_token);
	*tokens = jump_token;
	(*previous)->next = *tokens;
}

static int	parse_redirections_loop(t_list *tokens, t_redirection ***redirections)
{
	t_list	*previous;

	previous = NULL;
	while (tokens)
	{
		if (token_is_redirection(tokens))
		{
			if (!parse_one_redirection(tokens, redirections))
				return (0);
			delete_redirection_tokens(&tokens, &previous);
		}
		else
		{
			previous = tokens;
			tokens = tokens->next;
		}
	}
	return (1);
}

t_redirection	**parse_redirections(t_list *tokens)
{
	t_redirection	**redirections;

	redirections = (t_redirection**)malloc(sizeof(t_redirection) * 2);
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
	if (!parse_redirections_loop(tokens, &redirections))
	{
		free(redirections[IN]);
		free(redirections[OUT]);
		return (free_return_null(redirections));
	}
	return (redirections);
}

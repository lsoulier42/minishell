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

int	create_empty_file_redirection(char *filename, int append)
{
	int	fd;
	int	close_return;

	if (append)
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

int	parse_one_redirection(t_list *tokens, t_redirection **redirection)
{
	char	*value;
	char	*filename;
	int		append;
	int		export;

	value = get_token_value(tokens);
	filename = sub_quote(get_token_value(tokens->next));
	if (!filename)
		return (0);
	append = ft_strcmp(value, ">>") == 0;
	export = ft_strcmp(value, ">") == 0 || append;
	if (redirection_is_not_last(tokens) && export)
	{
		if (!create_empty_file_redirection(filename, append))
			return (free_return_int(filename));
	}
	else
	{
		*redirection = new_redirection(filename, export, append);
		if (!(*redirection))
			return (free_return_int(filename));
	}
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

t_redirection	*parse_redirections(t_list *tokens)
{
	t_redirection	*redirection;
	t_list			*previous;

	redirection = NULL;
	previous = NULL;
	while (tokens)
	{
		if (token_is_redirection(tokens))
		{
			if (!parse_one_redirection(tokens, &redirection))
				return (NULL);
			delete_redirection_tokens(&tokens, &previous);
		}
		else
		{
			previous = tokens;
			tokens = tokens->next;
		}
	}
	if (!redirection)
		redirection = new_redirection(NULL, 0, 0);
	return (redirection);
}

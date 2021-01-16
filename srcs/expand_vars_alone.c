/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars_alone.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 18:02:11 by lsoulier          #+#    #+#             */
/*   Updated: 2021/01/15 18:02:19 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**token_to_double_tab(t_list *begin)
{
	char	**new;
	int		i;
	char	*value;
	int		len;

	i = 0;
	len = ft_lstsize(begin);
	new = (char**)malloc(sizeof(char*) * (len + 1));
	if (!new)
		return (NULL);
	while (begin)
	{
		value = get_token_value(begin);
		new[i] = ft_strdup(value);
		if (!new[i])
			return (ft_double_tab_free(new));
		i++;
		begin = begin->next;
	}
	new[i] = NULL;
	return (new);
}

void	rm_token_replaced(t_list **args, int index)
{
	t_list	*tmp;
	t_list	*track;
	int		current;

	current = 0;
	track = *args;
	if (index == 0)
	{
		*args = track->next;
		del_token(track->content);
		free(track);
	}
	else
	{
		while (current != index - 1)
		{
			current++;
			track = track->next;
		}
		tmp = track->next->next;
		del_token(track->next->content);
		free(track->next);
		track->next = tmp;
	}
}

void	insert_tokens(t_list *token_before, t_list *list_to_insert)
{
	t_list *tmp;

	tmp = token_before->next;
	token_before->next = list_to_insert;
	while (list_to_insert->next)
		list_to_insert = list_to_insert->next;
	list_to_insert->next = tmp;
}

char	**insert_new_args(char *var_value, char **args,
	int *arg_index, int *argc)
{
	t_list	*token_args;
	t_list	*token_parsed;
	int		index_to_jump;
	char	**new;

	token_parsed = lexer(var_value, 1);
	if (!token_parsed)
		return (NULL);
	index_to_jump = ft_lstsize(token_parsed);
	token_args = double_tab_to_tokens(args);
	if (!token_args)
	{
		ft_lstclear(&token_parsed, &del_token);
		return (NULL);
	}
	insert_tokens(ft_lstat(token_args, *arg_index), token_parsed);
	rm_token_replaced(&token_args, *arg_index);
	*arg_index += index_to_jump - 1;
	*argc += index_to_jump - 1;
	new = token_to_double_tab(token_args);
	ft_lstclear(&token_args, &del_token);
	return (new);
}

int		expand_one_var_alone(t_data *msh_data, char ***args,
	int *arg_index, int *argc)
{
	t_var	*var;
	char	**new_args;
	char	*var_value;

	var = get_env_var(msh_data->begin_env, (*args)[*arg_index] + 1);
	if (var)
	{
		var_value = ft_strdup(var->value);
		if (!var_value)
			return (0);
		new_args = insert_new_args(var_value, *args, arg_index, argc);
		if (!new_args)
			return (free_return_int(var_value));
		ft_double_tab_free(*args);
		free(var_value);
		*args = new_args;
	}
	else
	{
		free((*args)[*arg_index]);
		(*args)[*arg_index] = NULL;
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 18:29:18 by lsoulier          #+#    #+#             */
/*   Updated: 2020/12/30 18:29:29 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

int		expand_vars(t_data *msh_data, t_cmd *cmd)
{
	int		i;

	i = -1;
	while (cmd->args[++i])
	{
		if (!expand_one_arg(msh_data, &cmd->args[i]))
			return (0);
	}
	return (1);
}

char *expand_get_var_key(char *unparsed)
{
	int		i;
	char	*key;

	i = 0;
	unparsed++;
	while (unparsed[i] && (ft_isalnum(unparsed[i]) || unparsed[i] == '_'))
		i++;
	key = ft_strndup(unparsed, i);
	return (key);
}

int flush_buffer(t_list **begin, char buffer[BUFFER_SIZE + 1], int *nb_read)
{
	char	*cpy_buffer;
	t_list	*el;

	buffer[*nb_read] = '\0';
	cpy_buffer = ft_strdup(buffer);
	if (!cpy_buffer)
	{
		ft_lstclear(begin, &free);
		return (0);
	}
	*nb_read = 0;
	el = ft_lstnew(cpy_buffer);
	if (!el)
	{
		ft_lstclear(begin, &free);
		return (free_return_int(cpy_buffer));
	}
	ft_lstadd_back(begin, el);
	return (1);
}

int		is_weakquote_specchar(char c)
{
	return (c == '$' || c == '`' || c == '"' || c == '\n' || c == '\\');
}

int 	is_specchar(char c)
{
	return (ft_isseparator(c) || c == '#' || c == '$' || c == '\\');
}

int expand_is_printable(char *arg, int i, char quote_char)
{
	return ((!ft_isquote(arg[i]) && arg[i] != '\\' && arg[i] != '$')
		|| (arg[i] == '$' && (ft_isspace(arg[i + 1]) || arg[i + 1] == '\0'))
		|| (quote_char == '\'' && arg[i] != quote_char)
		|| (quote_char == '"' && arg[i] == quote_char && is_escaped(arg, i))
		|| (quote_char == '"' && arg[i] == '\'')
		|| (quote_char == '"' && arg[i] == '\\'
			&& (!is_weakquote_specchar(arg[i + 1]) || is_escaped(arg, i)))
		|| (quote_char == '\0' && arg[i] == '\\'
			&& (is_escaped(arg, i) || !is_specchar(arg[i + 1])))
		|| (quote_char != '\'' && arg[i] == '$' && is_escaped(arg, i)));
}

int expand_last_return(t_data *msh_data, t_list **begin, int *i)
{
	char	*value;
	t_list 	*el;

	value = ft_itoa(msh_data->last_return);
	if (!value)
	{
		ft_lstclear(begin, &free);
		return (0);
	}
	el = ft_lstnew(value);
	if (!el)
		return (free_return_int(value));
	*i += 1;
	ft_lstadd_back(begin, ft_lstnew(value));
	return (1);
}

int expand_one_var(t_data *msh_data, t_list **begin, char *arg, int *i)
{
	char	*key;
	char	*value;
	t_var	*var;

	if (ft_isdigit(arg[*i + 1]))
		(*i)++;
	else
	{
		key = expand_get_var_key(arg + *i);
		var = get_env_var(msh_data->begin_env, key);
		if (var)
		{
			value = ft_strdup(var->value);
			if (!value)
			{
				ft_lstclear(begin, &free);
				free(key);
				return (0);
			}
			ft_lstadd_back(begin, ft_lstnew(value));
		}
		*i += ft_strlen(key);
		free(key);
	}
	return (1);
}

int expand_is_expandable_var(char *arg, int i, char quote_char)
{
	return (quote_char != '\'' && arg[i] == '$' && !is_escaped(arg, i)
		&& (ft_isalnum(arg[i + 1]) || arg[i + 1] == '_'));
}

int expand_is_last_return_var(char *arg, int i, char quote_char)
{
	return (quote_char != '\'' && arg[i] == '$'
		&& !is_escaped(arg, i) && arg[i + 1] == '?');
}

char expand_set_quote_char(char quote_char, char *arg, int i)
{
	if (!quote_char && ft_isquote(arg[i]) && !is_escaped(arg, i))
		quote_char = arg[i];
	else if ((quote_char == '\'' && arg[i] == '\'')
		|| (quote_char == '"' && arg[i] == '"' && !is_escaped(arg, i)))
		quote_char = '\0';
	return (quote_char);
}

int expand_is_flushable_buffer(char *arg, int i, int j, char quote_char)
{
	return (j == BUFFER_SIZE || expand_is_expandable_var(arg, i, quote_char)
		|| expand_is_last_return_var(arg, i, quote_char));
}

void expand_init_var(int *i, int *j, char *quote_char, t_list **begin)
{
	*quote_char = '\0';
	*i = -1;
	*j = 0;
	*begin = NULL;
}

int expand_one_arg_finish(char **arg_ptr, t_list **begin, char buffer[BUFFER_SIZE + 1], int *j)
{
	if (!flush_buffer(begin, buffer, j))
		return (0);
	free(*arg_ptr);
	*arg_ptr = ft_lstjoin(*begin);
	ft_lstclear(begin, &free);
	return (1);
}

int	expand_one_arg(t_data *msh_data, char **arg_ptr)
{
	char	quote_char;
	char	buffer[BUFFER_SIZE + 1];
	int		i;
	int 	j;
	t_list	*begin;

	expand_init_var(&i, &j, &quote_char, &begin);
	while ((*arg_ptr)[++i])
	{
		if (expand_is_flushable_buffer(*arg_ptr, i, j, quote_char))
			if(!flush_buffer(&begin, buffer, &j))
				return (0);
		if (expand_is_printable(*arg_ptr, i, quote_char))
			buffer[j++] = (*arg_ptr)[i];
		quote_char = expand_set_quote_char(quote_char, *arg_ptr, i);
		if (expand_is_expandable_var(*arg_ptr, i, quote_char))
			if (!expand_one_var(msh_data, &begin, *arg_ptr, &i))
				return (0);
		if (expand_is_last_return_var(*arg_ptr, i, quote_char))
			if (!expand_last_return(msh_data, &begin, &i))
				return (0);
	}
	if (!expand_one_arg_finish(arg_ptr, &begin, buffer, &j))
		return (0);
	return (1);
}



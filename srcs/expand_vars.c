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

int		expand_vars(t_data *msh_data, t_cmd *cmd)
{
	int		i;

	i = -1;
	while (cmd->args[++i])
	{
		if (cmd->args[i][0] == '$' && !str_has_ws(cmd->args[i]))
		{
			if (!expand_one_var_alone(msh_data, &(cmd->args), &i))
				return (0);
		}
		else
			if (!expand_one_arg(msh_data, &cmd->args[i]))
				return (0);
	}
	if (!trail_null_args(cmd))
		return (0);
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
		if (var && var->value)
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

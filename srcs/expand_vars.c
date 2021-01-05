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

int	expand_vars(t_data *msh_data, t_cmd *cmd)
{
	int		i;

	i = -1;
	while (cmd->args[++i])
		if (!expand_one_arg_vars(msh_data, &(cmd->args[i])))
			return (0);
	return (1);
}

int	expand_one_arg_vars(t_data *msh_data, char **cur_arg)
{
	int	i;

	i = 0;
	while ((*cur_arg)[i])
	{
		if ((*cur_arg)[i] == '$' && (*cur_arg)[i + 1] != '\0'
			&& !ft_isspace((*cur_arg)[i + 1]) && (*cur_arg)[i + 1] != '$'
			&& (*cur_arg)[i + 1] != '?')
		{
			if (!expand_one_var(msh_data->begin_env, cur_arg, &i))
				return (0);
		}
		else if ((*cur_arg)[i] == '$' && (*cur_arg)[i + 1] == '?')
		{
			if (!expand_last_return(msh_data, cur_arg, &i))
				return (0);
		}
		else
			i++;
	}
	return (1);
}

int	expand_one_var(t_list *begin_env, char **cur_arg, int *index)
{
	int		key_len;
	char	*var_value;
	char	*new_cur_arg;

	key_len = 0;
	var_value = expand_get_var_value(begin_env, *cur_arg + *index + 1, &key_len);
	if (!var_value)
		return (0);
	new_cur_arg = (char*)ft_calloc(ft_strlen(*cur_arg)
		- key_len + ft_strlen(var_value), sizeof(char));
	if (!new_cur_arg)
		return (free_return_int(var_value));
	ft_strlcpy(new_cur_arg, *cur_arg, *index + 1);
	ft_strcat(new_cur_arg, var_value);
	ft_strcat(new_cur_arg, *cur_arg + *index + key_len + 1);
	free(*cur_arg);
	*index += ft_strlen(var_value);
	free(var_value);
	*cur_arg = new_cur_arg;
	return (1);
}

char	*expand_get_var_value(t_list *begin_env, char *str, int *len)
{
	char	*key;
	t_var	*var;
	char	*value;

	if (ft_isdigit(str[0]))
	{
		*len = 1;
		return (ft_strdup(""));
	}
	else
		while (str[*len] && (ft_isalnum(str[*len]) || str[*len] == '_'))
			*len += 1;
	key = ft_strndup(str, *len);
	if (!key)
		return (NULL);
	var = get_env_var(begin_env, key);
	if (!var)
		value = ft_strdup("");
	else
		value = ft_strdup(var->value);
	free(key);
	return (value);
}

int	expand_last_return(t_data *msh_data, char **cur_arg, int *index)
{
	char	*itoa_value;
	int		itoa_len;
	char	*new_cur_arg;

	itoa_value = ft_itoa(msh_data->last_return);
	if (!itoa_value)
		return (0);
	itoa_len = ft_strlen(itoa_value);
	new_cur_arg = (char*)ft_calloc(ft_strlen(*cur_arg)
		+ itoa_len - 1, sizeof(char));
	if (!new_cur_arg)
		return (free_return_int(itoa_value));
	ft_strlcpy(new_cur_arg, *cur_arg, *index + 1);
	ft_strcat(new_cur_arg, itoa_value);
	ft_strcat(new_cur_arg, *cur_arg + *index + 3);
	free(*cur_arg);
	*index += itoa_len;
	free(itoa_value);
	*cur_arg = new_cur_arg;
	return (1);
}

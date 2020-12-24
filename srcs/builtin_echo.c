/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                      :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 14:43:17 by lsoulier          #+#    #+#             */
/*   Updated: 2020/12/24 15:08:52 by louise           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

char	*get_key(char *param)
{
	char	*key;
	int 	key_len;

	key_len = 0;
	while (param[key_len] && param[key_len] != ' ')
		key_len++;
	key = (char*)malloc(sizeof(char) * (key_len + 1));
	if (key)
		ft_strlcpy(key, param, key_len + 1);
	return (key);
}

void 	count_echo_var(char **param, t_data *msh_data, int *total_len)
{
	t_var		*var;
	char 		*key;
	int 		key_len;

	key = get_key(++(*param));
	if (key)
	{
		key_len = ft_strlen(key);
		var = get_env_var(msh_data->begin_env, key);
		if (var != NULL)
		{
			*total_len += ft_strlen(var->value);
			*param += ft_strlen(var->key);
		}
		else
			*param += key_len;
		free(key);
	}
}

int 	count_echo(char *param, t_data *msh_data)
{
	int	total_len;

	total_len = 0;
	while (*param)
	{
		if (*param != '$')
		{
			total_len++;
			param++;
		}
		else
		{
			if (param[1] == '?')
			{
				param += 2;
				total_len += itoa_count_char(msh_data->last_return);
			}
			else
				count_echo_var(&param, msh_data, &total_len);
		}
	}
	return (total_len);
}

void 	process_echo_var(char **param, t_data *msh_data, char **new_str, int *i)
{
	t_var		*var;
	char 		*key;
	char 		*itoa_str;

	if (*param[1] == '?')
	{
		*param += 2;
		itoa_str = ft_itoa(msh_data->last_return);
		ft_strcpy(*new_str + *i, itoa_str);
		*i += itoa_count_char(msh_data->last_return);
		free(itoa_str);
	}
	else
	{
		key = get_key(++(*param));
		if (key) {
			var = get_env_var(msh_data->begin_env, key);
			if (var != NULL)
			{
				ft_strcpy(*new_str + *i, var->value);
				*i += ft_strlen(var->value);
				*param += ft_strlen(var->key);
			} else
				*param += ft_strlen(key);
			free(key);
		}
	}
}

char	*process_echo(char *param, t_data *msh_data)
{
	char		*new_str;
	int			len;
	int			i;

	len = count_echo(param, msh_data);
	i = 0;
	new_str = (char*)ft_calloc(sizeof(char), (len + 1));
	if (new_str)
	{
		while (*param)
		{
			if (*param != '$')
				new_str[i++] = *param++;
			else
				process_echo_var(&param, msh_data, &new_str, &i);
		}
	}
	return (new_str);
}



/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 14:34:46 by lsoulier          #+#    #+#             */
/*   Updated: 2020/12/22 14:34:48 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list_env	*set_envlist(char *envp[])
{
	int i;
	t_list_env	*new_var;
	t_list_env	*begin;

	i = -1;
	begin = NULL;
	while (envp[++i])
	{
		new_var = set_envlist_var(envp[i]);
		if (!new_var)
		{
			env_clear(&begin);
			break;
		}
		env_add_back(&begin, new_var);
	}
	return (begin);
}

t_list_env	*set_envlist_var(char *env_var)
{
	char		*key;
	char		*value;
	int			key_len;
	int 		value_len;
	t_list_env	*new;

	key_len = 0;
	while (env_var[key_len] && env_var[key_len] != '=')
		key_len++;
	key = (char*)malloc(sizeof(char) * (key_len + 1));
	if (!key)
		return (NULL);
	ft_strlcpy(key, env_var, key_len + 1);
	value_len = ft_strlen(env_var) - key_len - 1;
	value = (char*)malloc(sizeof(char) * (value_len + 1));
	if (!value)
		return (NULL);
	ft_strlcpy(value, env_var + key_len + 1, value_len + 1);
	new = env_new_var(key, value);
	return (new);
}

char		*get_env_value(t_list_env *begin, char *key)
{
	char		*value;

	value = NULL;
	while (begin && !value)
	{
		if (ft_strcmp(key, begin->key) == 0)
			value = begin->value;
		begin = begin->next;
	}
	return (value);
}

void 	print_env(t_list_env *begin)
{
	while (begin)
	{
		ft_putstr(begin->key);
		ft_putstr("=");
		ft_putstr(begin->value);
		ft_putstr("\n");
		begin = begin->next;
	}
}

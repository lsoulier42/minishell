/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 14:34:46 by lsoulier          #+#    #+#             */
/*   Updated: 2020/12/24 15:13:22 by louise           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*set_env(char *envp[])
{
	int		i;
	t_list	*begin_env;
	char	*key;
	char	*value;

	i = -1;
	begin_env = NULL;
	while (envp[++i])
	{
		if (!parse_var(envp[i], &key, &value))
			return (0);
		if (!set_env_var(&begin_env, key, value))
		{
			ft_lstclear(&begin_env, &del_var);
			return (0);
		}
	}
	if (!change_env_shlvl(begin_env))
		return (NULL);
	return (begin_env);
}

t_var	*get_env_var(t_list *begin_env, char *key)
{
	t_var		*found_var;
	t_var		*var_cast;
	t_list		*env;

	found_var = NULL;
	env = begin_env;
	while (env && !found_var)
	{
		var_cast = (t_var*)env->content;
		if (ft_strcmp(key, var_cast->key) == 0)
			found_var = var_cast;
		env = env->next;
	}
	return (found_var);
}

int		change_env_var(t_list *begin_env, char *key, char *new_value)
{
	t_var	*var;
	char	**value_ref;

	var = get_env_var(begin_env, key);
	if (!var)
	{
		key = ft_strdup(key);
		if (!key)
			return (0);
		new_value = ft_strdup(new_value);
		if (!new_value)
			return (free_return_int(key));
		if (!set_env_var(&begin_env, key, new_value))
		{
			free(key);
			return (free_return_int(new_value));
		}
		return (1);
	}
	value_ref = &(var->value);
	free(var->value);
	*value_ref = new_value;
	return (1);
}

int		set_env_var(t_list **begin_env, char *key, char *value)
{
	t_var	*var;
	t_list	*el;

	var = new_var(key, value);
	if (!var)
		return (0);
	el = ft_lstnew(var);
	if (!el)
		return (0);
	ft_lstadd_back(begin_env, el);
	return (1);
}

void	print_env_fd(t_list *begin_env, int fd)
{
	t_var	*cast;
	t_list	*env;

	env = begin_env;
	while (env)
	{
		cast = (t_var*)env->content;
		ft_putstr_fd(cast->key, fd);
		ft_putstr_fd("=", fd);
		ft_putstr_fd(cast->value, fd);
		ft_putstr_fd("\n", fd);
		env = env->next;
	}
}

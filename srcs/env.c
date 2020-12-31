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

t_list	*g_env_list_begin;

t_list	*set_env(char *envp[])
{
	int		i;
	t_list	*begin_env;

	i = -1;
	begin_env = NULL;
	while (envp[++i])
	{
		if (!set_env_var(&begin_env, envp[i]))
		{
			ft_lstclear(&begin_env, &del_var);
			return (NULL);
		}
	}
	return (begin_env);
}

t_var	*get_env_var(char *key)
{
	t_var		*found_var;
	t_var		*var_cast;
	t_list		*env;

	found_var = NULL;
	env = g_env_list_begin;
	while (env && !found_var)
	{
		var_cast = (t_var*)env->content;
		if (ft_strcmp(key, var_cast->key) == 0)
			found_var = var_cast;
		env = env->next;
	}
	return (found_var);
}

int	set_env_var(t_list **begin_env, char *unparsed)
{
	t_var	*new_var;
	t_list	*el;

	new_var = parse_var(unparsed);
	if (!new_var)
		return (0);
	el = ft_lstnew(new_var);
	if (!el)
	{
		del_var(new_var);
		return (0);
	}
	ft_lstadd_back(begin_env, el);
	return (1);
}

void 	print_env(void)
{
	t_var	*cast;
	t_list	*env;

	env = g_env_list_begin;
	while (env)
	{
		cast = (t_var*)env->content;
		ft_putstr(cast->key);
		ft_putstr("=");
		ft_putstr(cast->value);
		ft_putstr("\n");
		env = env->next;
	}
}

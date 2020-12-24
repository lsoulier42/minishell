/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 14:34:46 by lsoulier          #+#    #+#             */
/*   Updated: 2020/12/24 14:48:15 by louise           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*set_env(char *envp[])
{
	int i;
	t_list	*begin_env;

	i = -1;
	begin_env = NULL;
	while (envp[++i])
	{
		if (!set_env_var(&begin_env, envp[i]))
		{
			ft_lstclear(&begin_env, &del_var);
			break;
		}
	}
	return (begin_env);
}

t_var	*get_env_var(t_list *begin_env, char *key)
{
	t_var		*found_var;
	t_var		*var_cast;

	found_var = NULL;
	while (begin_env && !found_var)
	{
		var_cast = (t_var*)begin_env->content;
		if (ft_strcmp(key, var_cast->key) == 0)
			found_var = var_cast;
		begin_env = begin_env->next;
	}
	return (found_var);
}

int		set_env_var(t_list **begin_env, char *unparsed)
{
	t_var	*new_var;
	t_list	*el;

	new_var = parse_var(unparsed);
	el = ft_lstnew(new_var);
	if (!el)
		return (0);
	ft_lstadd_back(begin_env, el);
	return (1);
}

void 	print_env(t_list *begin_env)
{
	t_var *cast;

	while (begin_env)
	{
		cast = (t_var*)begin_env->content;
		ft_putstr(cast->key);
		ft_putstr("=");
		ft_putstr(cast->value);
		ft_putstr("\n");
		begin_env = begin_env->next;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 03:57:26 by lsoulier          #+#    #+#             */
/*   Updated: 2020/12/31 03:57:32 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*serialize_one_env_var(t_list *env_el)
{
	char	*str;
	int		len;
	t_var	*var;

	var = (t_var*)env_el->content;
	len = ft_strlen(var->key) + ft_strlen(var->value) + 1;
	str = (char*)ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	ft_strcat(str, var->key);
	ft_strcat(str, "=");
	ft_strcat(str, var->value);
	return (str);
}

char	**serialize_env(t_list *begin_env)
{
	int		len;
	char	**envp;
	t_list	*env;
	int		var_nb;

	env = begin_env;
	len = ft_lstsize(env);
	var_nb = 0;
	envp = (char**)malloc(sizeof(char*) * (len + 1));
	if (!envp)
		return (NULL);
	while (env)
	{
		envp[var_nb] = serialize_one_env_var(env);
		if (!envp[var_nb++])
			return (ft_free_double_tab(envp));
		env = env->next;
	}
	envp[var_nb] = NULL;
	return (envp);
}

int		env_key_exist(t_list *begin_env, char *key)
{
	t_list	*env;
	t_var	*var;

	env = begin_env;
	while (env)
	{
		var = (t_var*)env->content;
		if (ft_strcmp(var->key, key) == 0)
			return (1);
		env = env->next;
	}
	return (0);
}

int		change_env_shlvl(t_list *begin_env)
{
	t_var	*shlvl;
	char	*itoa_value;

	shlvl = get_env_var(begin_env, "SHLVL");
	if (!shlvl)
	{
		itoa_value = ft_strdup("1");
		if (!itoa_value)
			return (0);
		if (!set_env_var(&begin_env, "SHLVL", itoa_value))
			return (0);
	}
	else
	{
		itoa_value = ft_itoa(ft_atoi(shlvl->value) + 1);
		if (!itoa_value)
			return (0);
		change_env_var(begin_env, "SHLVL", itoa_value);
	}
	return (1);
}

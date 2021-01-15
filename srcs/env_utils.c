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
	len = ft_strlen(var->key) + 1;
	if (var->value)
		len += ft_strlen(var->value);
	str = (char*)ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	ft_strcat(str, var->key);
	ft_strcat(str, "=");
	if (var->value)
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
			return (ft_double_tab_free(envp));
		env = env->next;
	}
	envp[var_nb] = NULL;
	return (envp);
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
		if (!set_env_var(&begin_env, ft_strdup("SHLVL"), itoa_value))
			return (free_return_int(itoa_value));
	}
	else
	{
		itoa_value = ft_itoa(ft_atoi(shlvl->value) + 1);
		if (!itoa_value)
			return (0);
		if(!change_env_var(begin_env, "SHLVL", itoa_value))
			return (free_return_int(itoa_value));
	}
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
		if (cast)
		{
			if (cast->key)
				ft_putstr_fd(cast->key, fd);
			ft_putstr_fd("=", fd);
			if (cast->value)
				ft_putstr_fd(cast->value, fd);
			ft_putstr_fd("\n", fd);
		}
		env = env->next;
	}
}

t_list *create_basic_env(void)
{
	char **fake_envp;
	char *cur_dir;
	char *pwd;
	t_list *begin;

	cur_dir = getcwd(NULL, 0);
	if (!cur_dir)
		return (NULL);
	pwd = ft_strjoin("PWD=", cur_dir);
	if (!pwd)
		return(free_return_null(cur_dir));
	free(cur_dir);
	fake_envp = (char*[]){"SHLVL=0", pwd, "_=/usr/bin/env", NULL};
	begin = set_env_loop(fake_envp);
	free(pwd);
	return (begin);
}

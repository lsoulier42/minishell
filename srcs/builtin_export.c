/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 02:19:52 by lsoulier          #+#    #+#             */
/*   Updated: 2020/12/31 02:19:59 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int 	export_arg_is_legit(char *str)
{
	int len_to_equal;

	len_to_equal = 0;
	if (ft_isdigit(str[0]) || str[0] == '=')
		return (0);
	while (str[len_to_equal] && str[len_to_equal] != '=')
	{
		if (!ft_isalnum(str[len_to_equal]) && str[len_to_equal] != '_')
			return (0);
		len_to_equal++;
	}
	if (str[len_to_equal] != '=')
		return (0);
	return (1);
}

int 	export_key_already_exist(char *key)
{
	t_list	*env;
	t_var	*var;

	env = g_env_list_begin;
	while (env)
	{
		var = (t_var*)env->content;
		if (ft_strcmp(var->key, key) == 0)
			return (1);
		env = env->next;
	}
	return (0);
}

int		export_change_value(char *unparsed, char *key)
{
	char 	*value;

	value = parse_var_value(unparsed);
	if (!value)
		return (0);
	if (!change_env_var_value(key, value))
		return (0);
	return (1);
}

int		exec_export(t_data *msh_data, t_cmd *cmd)
{
	int 	i;
	char 	*key;
	int 	error_occurred;

	i = -1;
	while (cmd->args[++i])
	{
		if (export_arg_is_legit(cmd->args[i]))
		{
			key = parse_var_key(cmd->args[i]);
			if (!key)
				return (-1);
			if (export_key_already_exist(key))
				error_occurred = export_change_value(cmd->args[i], key);
			else
				error_occurred = set_env_var(&g_env_list_begin, cmd->args[i]);
			free(key);
		}
	}
	if (error_occurred == 0)
		return (-1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 16:03:01 by lsoulier          #+#    #+#             */
/*   Updated: 2020/12/24 16:04:18 by louise           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		exec_export(char *cmd, t_data *msh_data)
{
	char	*param;
	int		r_cmd;

	param = get_param(cmd, "export");
	if (!param)
		return (0);
	r_cmd = set_env_var(&msh_data->begin_env, param);
	free(param);
	return (r_cmd);
}

int		exec_pwd(char *cmd, t_data *msh_data)
{
	t_var	*pwd;

	pwd = get_env_var(msh_data->begin_env, "PWD");
	if (!pwd)
		return (0);
	ft_putendl_fd(pwd->value, 1);
	return (1);
}

int exec_env(char *cmd, t_data *msh_data)
{
	print_env(msh_data->begin_env);
	return (1);
}

int	exec_unset(char *cmd, t_data *msh_data)
{
	char	*param;
	t_var	param_var;

	param = get_param(cmd, "unset");
	if (!param)
		return (0);
	set_var(&param_var, param, NULL);
	free(param);
	ft_lstrm_if(&msh_data->begin_env, &param_var, &cmp_key_var, &del_var);
	return (1);
}
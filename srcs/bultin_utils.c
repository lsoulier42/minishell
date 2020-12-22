/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bultin_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 22:56:47 by lsoulier          #+#    #+#             */
/*   Updated: 2020/12/22 22:57:21 by louise           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_param(char *cmd, char *bultin_name)
{
	char *param;
	int bultin_len;

	bultin_len = ft_strlen(bultin_name) + 1; //to trim space
	param = ft_substr(cmd, bultin_len, ft_strlen(cmd) - bultin_len - 1); //to trim \n
	return (param);
}

int	exec_export(char *cmd, t_data *mshl_data)
{
	char *param;
	t_list_env *el;

	param = get_param(cmd, "export");
	if (!param)
		return (0);
	el = set_envlist_var(param);
	free(param);
	if (!el)
		return (0);
	env_add_back(&mshl_data->begin_env, el);
	return (1);
}

int exec_pwd(char *cmd, t_data *mshl_data)
{
	ft_putendl_fd(get_env_value(mshl_data->begin_env, "PWD"), 1);
	return (1);
}

int exec_cd(char *cmd, t_data *mshl_data)
{
	ft_putstr("cd is not implemented yet\n");
	return (1);
}

int exec_echo(char *cmd, t_data *mshl_data)
{
	char *param;

	param = get_param(cmd, "echo");
	if (!param)
		return (0);
	ft_putendl_fd(param, 1);
	free(param);
	return (1);
}
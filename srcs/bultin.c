/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bultin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 22:10:20 by lsoulier          #+#    #+#             */
/*   Updated: 2020/12/22 22:53:17 by louise           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int search_cmd(char *cmd)
{
	char	**bultin;
	int		i;

	i = -1;
	bultin = (char *[8]){"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};
	while (bultin[++i])
		if (ft_strstr(cmd, bultin[i]) != NULL)
			return (1);
	return (0);
}

int execute_cmd(char *cmd, t_data *mshl_data)
{
	char	**bultin;
	int		(*bultin_fct[8])(char *cmd, t_data *mshl_data);
	int		i;

	bultin = (char *[8]){"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};
	i = -1;
	bultin_fct[0] = &exec_echo;
	bultin_fct[1] = &exec_cd;
	bultin_fct[2] = &exec_pwd;
	bultin_fct[3] = &exec_export;
	bultin_fct[4] = &exec_unset;
	bultin_fct[5] = &exec_env;
	bultin_fct[6] = &exec_exit;
	while (bultin[++i])
		if (ft_strstr(cmd, bultin[i]) != NULL)
			return ((*bultin_fct[i])(cmd, mshl_data));
	return (0);
}

int exec_exit(char *cmd, t_data *mshl_data)
{
	mshl_data->exit_mshl = 1;
	return (1);
}

int exec_env(char *cmd, t_data *mshl_data)
{
	print_env(mshl_data->begin_env);
	return (1);
}

int	exec_unset(char *cmd, t_data *mshl_data)
{
	char *param;
	t_list_env *el;

	param = get_param(cmd, "unset");
	if (!param)
		return (0);
	el = mshl_data->begin_env;
	while (el && ft_strcmp(el->key, param) != 0)
		el = el->next;
	free(param);
	if (!el)
	{
		ft_putstr("Environment variable not found.\n");
		return (0);
	}
	env_del_var(&mshl_data->begin_env, el);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 16:03:01 by lsoulier          #+#    #+#             */
/*   Updated: 2020/12/25 22:15:10 by louise           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		exec_export(t_data *msh_data, t_cmd *cmd)
{
	int		r_cmd;
	int 	i;

	i = -1;
	while (cmd->params[++i])
		r_cmd = set_env_var(&msh_data->begin_env, cmd->params[i]);
	return (r_cmd);
}

int		exec_pwd(t_data *msh_data, t_cmd *cmd)
{
	t_var	*pwd;

	pwd = get_env_var(msh_data->begin_env, "PWD");
	if (!pwd)
		return (0);
	ft_putendl_fd(pwd->value, 1);
	return (1);
}

int exec_env(t_data *msh_data, t_cmd *cmd)
{
	print_env(msh_data->begin_env);
	return (1);
}

int	exec_unset(t_data *msh_data, t_cmd *cmd)
{
	int		i;
	t_var	*current;

	i = -1;
	while (cmd->params[++i])
	{
		current = get_env_var(msh_data->begin_env, cmd->params[i]);
		if (current)
			ft_lstrm_if(&msh_data->begin_env, &current,
			   &cmp_key_var, &del_var);
	}
	return (1);
}
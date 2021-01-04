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

int	exec_pwd(t_data *msh_data, t_cmd *cmd)
{
	char *pathname;

	pathname = (get_env_var(msh_data->begin_env, "PWD"))->value;
	ft_putendl_fd(pathname, STDOUT_FILENO);
	return (0);
}

int	exec_env(t_data *msh_data, t_cmd *cmd)
{
	print_env(msh_data->begin_env);
	return (0);
}

int	exec_unset(t_data *msh_data, t_cmd *cmd)
{
	int		i;
	t_var	*to_remove;

	i = 0;
	while (cmd->args[++i])
	{
		to_remove = get_env_var(msh_data->begin_env, cmd->args[i]);
		if (to_remove != NULL)
			ft_lstrm_if(&(msh_data->begin_env), to_remove,
			   &cmp_key_var, del_var);
	}
	return (0);
}

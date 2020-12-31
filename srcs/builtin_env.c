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
	t_var	*pwd;

	pwd = get_env_var("PWD");
	if (!pwd)
		return (-1);
	ft_putendl_fd(pwd->value, 1);
	return (0);
}

int	exec_env(t_data *msh_data, t_cmd *cmd)
{
	print_env();
	return (0);
}

int	exec_unset(t_data *msh_data, t_cmd *cmd)
{
	int		i;
	t_var	*current;

	i = -1;
	while (cmd->args[++i])
	{
		current = get_env_var(cmd->args[i]);
		if (current)
			ft_lstrm_if(&(g_env_list_begin), current,
				&cmp_key_var, &del_var);
	}
	return (0);
}

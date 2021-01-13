/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 13:02:31 by lsoulier          #+#    #+#             */
/*   Updated: 2021/01/06 13:02:39 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int 	exec_cd_change_dir(t_data *msh_data, t_cmd *cmd, char *new_dir)
{
	int		chdir_return;
	char	*new_current;

	chdir_return = 0;
	if(!cmd->is_piped)
		chdir_return = chdir(new_dir);
	if (chdir_return == -1)
		format_error(cmd->args[0], new_dir, errno, NULL);
	new_current = getcwd(NULL, 0);
	if (!new_current)
		return (0);
	if(!exec_cd_change_env_var(msh_data,new_current) || chdir_return == -1)
	{
		free(new_current);
		return (0);
	}
	free(new_current);
	return (1);
}

int		exec_cd_home(t_data *msh_data, t_cmd *cmd)
{
	t_var *home;

	home = get_env_var(msh_data->begin_env, "HOME");
	if (!home)
		return (0);
	if (!exec_cd_change_dir(msh_data, cmd, home->value))
		return (0);
	return (1);
}

int		exec_cd_oldpwd(t_data *msh_data, t_cmd *cmd)
{
	t_var *oldpwd;

	oldpwd = get_env_var(msh_data->begin_env, "OLDPWD");
	if (!oldpwd)
		return (0);
	if (!exec_cd_change_dir(msh_data, cmd, oldpwd->value))
		return (0);
	return (1);
}

int		exec_cd(t_data *msh_data, t_cmd *cmd)
{
	char *new_dir;

	new_dir = cmd->args[1];
	if (!new_dir || (new_dir != NULL && ft_strcmp(new_dir, "~") == 0))
	{
		if (!exec_cd_home(msh_data, cmd))
			return (EXIT_FAILURE);
	}
	else if (ft_strcmp(new_dir, ".") == 0)
	{
		if (!exec_cd_current_dir(msh_data, cmd))
			return (EXIT_FAILURE);
	}
	else if (ft_strcmp(new_dir, "-") == 0)
	{
		if (!exec_cd_oldpwd(msh_data, cmd))
			return (EXIT_FAILURE);
	}
	else
		if (!exec_cd_change_dir(msh_data, cmd, new_dir))
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

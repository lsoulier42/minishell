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

int		exec_cd_particular_paths(t_data *msh_data, t_cmd *cmd,
	char *new_dir, char *oldpwd)
{
	t_var	*var;

	if (!new_dir || (new_dir != NULL && *new_dir == '~'))
	{
		var = get_env_var(msh_data->begin_env, "HOME");
		if (!var)
			return (0);
		new_dir = var->value;
	}
	else
	{
		var = get_env_var(msh_data->begin_env, "OLDPWD");
		if (!var)
			return (0);
		new_dir = var->value;
	}
	if (!exec_cd_change_dir(msh_data, cmd, new_dir, oldpwd))
		return (0);
	return (1);
}

int		exec_cd_env_var(t_list *begin_env, char *new_pathname, char *oldpwd)
{
	int	error;

	error = 0;
	if (!change_env_var(begin_env, "OLDPWD", oldpwd))
		error = 1;
	if (!change_env_var(begin_env, "PWD", new_pathname))
		error = 1;
	return (error == 0);
}

int		exec_cd_change_dir(t_data *msh_data,
	t_cmd *cmd, char *new_dir, char *oldpwd)
{
	char	*new_pathname;
	int		chdir_return;
	int		error;

	chdir_return = chdir(new_dir);
	error = 0;
	if (cmd->is_piped && chdir_return == 0)
		chdir(oldpwd);
	new_pathname = getcwd(NULL, 0);
	if (!new_pathname)
		return (0);
	if (chdir_return == 0)
		if (!exec_cd_env_var(msh_data->begin_env, new_pathname, oldpwd))
			error = 1;
	if (chdir_return == -1)
	{
		error = 1;
		format_error(cmd->args[0], new_dir, errno, NULL);
	}
	if (error == 1)
		free(new_pathname);
	return (error == 0);
}

int		exec_cd(t_data *msh_data, t_cmd *cmd)
{
	char	*new_dir;
	char	*oldpwd;

	new_dir = cmd->args[1];
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		return (-1);
	if (!new_dir || (new_dir != NULL && (*new_dir == '-' || *new_dir == '~')))
	{
		if (!exec_cd_particular_paths(msh_data, cmd, new_dir, oldpwd))
			return (free_return_int(oldpwd) + EXIT_FAILURE);
	}
	else
	{
		if (!exec_cd_change_dir(msh_data, cmd, new_dir, oldpwd))
			return (free_return_int(oldpwd) + EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

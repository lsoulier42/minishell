/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 00:38:46 by lsoulier          #+#    #+#             */
/*   Updated: 2021/01/13 00:38:52 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		exec_cd_current_dir(t_data *msh_data, t_cmd *cmd, char *new_dir)
{
	char	*current;

	current = getcwd(NULL, 0);
	if (!current)
		exec_cd_error_retrieving_cwd(msh_data, new_dir);
	if(!exec_cd_change_dir(msh_data, cmd, current))
	{
		free(current);
		return (0);
	}
	free(current);
	return (1);
}

int 	exec_cd_change_env_var(t_data *msh_data, char *new_dir)
{
	char	*new_pwd;
	char	*pwd_value;
	char 	*oldpwd;
	t_var	*pwd;

	pwd_value = "";
	pwd = get_env_var(msh_data->begin_env, "PWD");
	if (pwd)
		pwd_value = pwd->value;
	new_pwd = ft_strdup(new_dir);
	if (!new_pwd)
		return (0);
	oldpwd = ft_strdup(pwd_value);
	if (!oldpwd)
		return (free_return_int(new_pwd));
	if(!change_env_var(msh_data->begin_env, "PWD", new_pwd))
	{
		free(new_pwd);
		return (free_return_int(oldpwd));
	}
	if(!change_env_var(msh_data->begin_env, "OLDPWD", oldpwd))
	{
		free(new_pwd);
		return (free_return_int(oldpwd));
	}
	return (1);
}

int exec_cd_error_retrieving_cwd(t_data *msh_data, char *new_dir)
{
	t_var	*pwd;
	char	*pwd_value;
	char 	*join;

	cd_current_dir_error();
	pwd = get_env_var(msh_data->begin_env, "PWD");
	pwd_value = "";
	if (pwd)
		pwd_value = pwd->value;
	if(!(join = ft_strcmp(new_dir, ".") == 0 ?
		ft_strjoin(pwd_value, "/.") : ft_strjoin(pwd_value, "/..")))
		return (0);
	exec_cd_change_env_var(msh_data, join);
	free(join);
	return (1);
}

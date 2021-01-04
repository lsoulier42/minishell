/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                     :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 22:56:47 by lsoulier          #+#    #+#             */
/*   Updated: 2020/12/25 22:28:38 by louise           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int exec_cd_particular_paths(t_data *msh_data, char **new_dir)
{
    t_var   *home_var;

    if (ft_strcmp("~", *new_dir) == 0)
    {
        home_var = get_env_var(msh_data->begin_env, "HOME");
        if (!home_var)
            return (0);
        *new_dir = home_var->value;
    }
    else if (ft_strcmp("-", *new_dir) == 0)
    {
        home_var = get_env_var(msh_data->begin_env, "OLDPWD");
        if (!home_var)
            return (0);
        *new_dir = home_var->value;
    }
    return (1);
}

int	exec_cd(t_data *msh_data, t_cmd *cmd)
{
	char	*new_dir;
    char    *oldpwd;
	char	*new_pathname;
	int		chdir_return;

	new_dir = cmd->args[1];
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
	    return (-1);
	if (!exec_cd_particular_paths(msh_data, &new_dir))
	    return (free_return_int(oldpwd) - 1);
	chdir_return = chdir(new_dir);
	new_pathname = getcwd(NULL, 0);
	if (!new_pathname)
		return (free_return_int(oldpwd) - 1);
	if (chdir_return == 0)
	{
        change_env_var(msh_data->begin_env, "OLDPWD", oldpwd);
	    change_env_var(msh_data->begin_env, "PWD", new_pathname);
    }
	if (chdir_return == -1)
		format_error(cmd->name, new_dir, errno, NULL);
	return (chdir_return);
}

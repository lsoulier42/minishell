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
		cd_dir_not_found(new_dir);
	new_current = getcwd(NULL, 0);
	if (!new_current)
		return (0);
	if(!exec_cd_change_env_var(msh_data, new_current) || chdir_return == -1)
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
	{
		cd_var_unset("HOME");
		return (0);
	}
	if (home->value && ft_strcmp(home->value, "") != 0)
		if (!exec_cd_change_dir(msh_data, cmd, home->value))
			return (0);
	return (1);
}

int		exec_cd_oldpwd(t_data *msh_data, t_cmd *cmd)
{
	t_var *oldpwd;

	oldpwd = get_env_var(msh_data->begin_env, "OLDPWD");
	if (!oldpwd)
	{
		cd_var_unset("OLDPWD");
		return (0);
	}
	if (!exec_cd_change_dir(msh_data, cmd, oldpwd->value))
		return (0);
	else
		ft_putendl_fd(oldpwd->value, STDIN_FILENO);
	return (1);
}

int 	exec_cd_std(t_data *msh_data, t_cmd *cmd, char *new_dir)
{
	char	*cur_dir;
	t_var	*var;

	cur_dir = getcwd(NULL, 0);
	var = get_env_var(msh_data->begin_env, "PWD");
	if (!cur_dir && ft_strcmp(new_dir, "..") == 0
		&& var && ft_strrchr(var->value, '.') == NULL)
	{
		free(cur_dir);
		return (exec_cd_error_retrieving_cwd(msh_data, new_dir));
	}
	else
		return (exec_cd_change_dir(msh_data, cmd, new_dir));

}

int		exec_cd(t_data *msh_data, t_cmd *cmd)
{
	char	*new_dir;

	if (cmd->args[1] && cmd->args[2])
		return (cd_too_many_args());
	new_dir = cmd->args[1];
	if (!new_dir || (new_dir != NULL && ft_strcmp(new_dir, "~") == 0))
	{
		if (!exec_cd_home(msh_data, cmd))
			return (EXIT_FAILURE);
	}
	else if (ft_strcmp(new_dir, ".") == 0)
	{
		if (!exec_cd_current_dir(msh_data, cmd, new_dir))
			return (EXIT_FAILURE);
	}
	else if (ft_strcmp(new_dir, "-") == 0)
	{
		if (!exec_cd_oldpwd(msh_data, cmd))
			return (EXIT_FAILURE);
	}
	else
		if (!exec_cd_std(msh_data, cmd, new_dir))
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 14:46:30 by lsoulier          #+#    #+#             */
/*   Updated: 2021/01/03 14:46:39 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	search_in_dir(char *dirname, char *cmd_name)
{
	DIR				*cur_dir;
	struct dirent	*cur_dirent;
	int				finish;

	cur_dir = opendir(dirname);
	finish = 0;
	if (!cur_dir)
		return (0);
	while (!finish)
	{
		cur_dirent = readdir(cur_dir);
		if (!cur_dirent)
			finish = 1;
		if (!finish && ft_strcmp(cmd_name, cur_dirent->d_name) == 0)
		{
			closedir(cur_dir);
			return (1);
		}
	}
	closedir(cur_dir);
	return (0);
}

int	search_path_relative(t_data *msh_data, t_cmd **cmd)
{
	t_var	*path;
	char	**pathnames;
	int		i;

	if (!(path = get_env_var(msh_data->begin_env, "PATH")))
		return (0);
	if (!(pathnames = ft_split(path->value, ':')))
		return (0);
	i = -1;
	while (pathnames[++i])
	{
		if (search_in_dir(pathnames[i], (*cmd)->args[0]))
		{
			free((*cmd)->path);
			(*cmd)->path = ft_strjoin(pathnames[i], "/");
			free_double_tab_ret_int(pathnames);
			if (!((*cmd)->path))
				return (0);
			return (1);
		}
	}
	return (free_double_tab_ret_int(pathnames));
}

int	search_path(t_data *msh_data, t_cmd **cmd)
{
	if (!search_builtin((*cmd)->args[0]))
	{
		if ((*cmd)->args[0] && ft_strcmp((*cmd)->args[0], "") == 0)
			return (search_is_directory((*cmd)->path));
		else if (ft_strcmp((*cmd)->path, "") == 0)
		{
			if (ft_strcmp((*cmd)->args[0], "..") == 0
				|| ft_strcmp((*cmd)->args[0], ".") == 0
				|| !search_path_relative(msh_data, cmd))
			{
				command_not_found((*cmd)->args[0]);
				return (0);
			}
		}
		else
		{
			if (!search_in_dir((*cmd)->path, (*cmd)->args[0]))
			{
				directory_not_found((*cmd)->args[0]);
				return (0);
			}
		}
	}
	return (1);
}

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

int		search_in_dir(char *dirname, char *cmd_name)
{
	DIR				*cur_dir;
	struct dirent	*cur_dirent;
	int 			finish;

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

int search_path_relative_in_path(t_data *msh_data, t_cmd **cmd)
{
	t_var	*path;
	char	**pathnames;
	int		i;

	path = get_env_var(msh_data->begin_env, "PATH");
	if (!path)
		return (0);
	pathnames = ft_split(path->value, ':');
	if (!pathnames)
		return (0);
	i = -1;
	while (pathnames[++i])
		if (search_in_dir(pathnames[i], (*cmd)->args[0]))
		{
			free((*cmd)->path);
			(*cmd)->path = ft_strjoin(pathnames[i], "/");
			return (free_double_tab_ret_int(pathnames) + 1);
		}
	return (free_double_tab_ret_int(pathnames));
}

int search_path_relative(t_data *msh_data, t_cmd **cmd)
{
	char	*current_dir;
	char 	*cmd_name;

	current_dir = getcwd(NULL, 0);
	if (!current_dir)
		return (0);
	cmd_name = (*cmd)->args[0];
	if (ft_strncmp(cmd_name, "./", 2) == 0)
		cmd_name = ft_strchr(cmd_name, '/') + 1;
	if (!search_in_dir(current_dir, cmd_name))
	{
		free(current_dir);
		return (search_path_relative_in_path(msh_data, cmd));
	}
	else
	{
		if (ft_strncmp((*cmd)->args[0], "./", 2) != 0)
		{
			free((*cmd)->path);
			(*cmd)->path = ft_strjoin(current_dir, "/");
		}
		return (free_return_int(current_dir) + 1);
	}
}

int search_path(t_data *msh_data, t_cmd **cmd)
{
	if (!search_builtin((*cmd)->args[0]))
	{
		if (ft_strcmp((*cmd)->path, "") == 0)
		{
			if (!search_path_relative(msh_data, cmd))
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

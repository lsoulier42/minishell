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

char	*format_found_path(char *found, char *cmd_name)
{
	int		len;
	char	*path;

	len = ft_strlen(found) + 1 + ft_strlen(cmd_name);
	path = (char*)ft_calloc(len + 1, sizeof(char));
	if (!path)
		return (NULL);
	ft_strcpy(path, found);
	ft_strcat(path, "/");
	ft_strcat(path, cmd_name);
	return (path);
}

char	*search_path_relative(t_list *begin_env, char *cmd_name)
{
	t_var 	*env_path;
	char	**pathnames;
	char	*found_pathname;
	char	*full_path;
	int 	i;

	i = -1;
	env_path = get_env_var(begin_env, "PATH");
	if (!env_path)
		return (NULL);
	pathnames = ft_split(env_path->value, ':');
	if (!pathnames)
		return (0);
	while (pathnames[++i])
		if (search_in_dir(pathnames[i], cmd_name))
			break ;
	found_pathname = pathnames[i];
	if (!found_pathname)
		return (ft_free_double_tab(pathnames));
	full_path = format_found_path(found_pathname, cmd_name);
	ft_free_double_tab(pathnames);
	return (full_path);
}

char	*search_path_absolute(t_list *begin_env, char *cmd_name)
{
	char	*format_path;

	if (cmd_name[0] == '/')
		format_path = search_path_absolute_std(cmd_name);
	else if (cmd_name[0] == '~')
		format_path = search_path_absolute_home(begin_env, cmd_name);
	else
		format_path = search_path_absolute_dot(begin_env, cmd_name);
	return (format_path);
}

char	*search_path(t_data *msh_data, char *cmd_name)
{
	char *full_path;

	if (search_builtin(cmd_name))
	    full_path = ft_strdup(cmd_name);
	else
	{
		if (cmd_name[0] == '/' || cmd_name[0] == '.' || cmd_name[0] == '~')
		{
			full_path = search_path_absolute(msh_data->begin_env, cmd_name);
			if (!full_path)
				directory_not_found(cmd_name);
		}
		else
		{
			full_path = search_path_relative(msh_data->begin_env, cmd_name);
			if (!full_path)
				command_not_found(cmd_name);
		}
	}
	free(cmd_name);
	return (full_path);
}

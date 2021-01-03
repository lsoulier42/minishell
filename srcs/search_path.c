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

int 	search_one_relative_path(char *pathname, char *cmd_name)
{
	DIR				*cur_dir;
	struct dirent	*cur_dirent;
	int 			finish;

	cur_dir = opendir(pathname);
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

char 	*format_found_path(char *found, char *cmd_name)
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

char 	*search_path_relative(t_list *begin_env, char *cmd_name)
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
		if (search_one_relative_path(pathnames[i], cmd_name))
			break ;
	found_pathname = pathnames[i];
	if (!found_pathname)
		return (free_double_tab(pathnames));
	full_path = format_found_path(found_pathname, cmd_name);
	free_double_tab(pathnames);
	return (full_path);
}

char 	*search_path_absolute(t_list *begin_env, char *cmd_name)
{
	char	*format_path;
	char 	*trim_cmd_name;
	char	*cur_dir;
	t_var 	*home;

	if (cmd_name[0] == '/')
		format_path = ft_strdup(cmd_name);
	else if (cmd_name[0] == '~')
	{
		home = get_env_var(begin_env, "HOME");
		if (!home)
			return (NULL);
		trim_cmd_name = ft_substr(cmd_name, 2, ft_strlen(cmd_name) - 2);
		if (!trim_cmd_name)
			return (NULL);
		format_path = format_found_path(home->value, trim_cmd_name);
		if (!format_path)
			return (free_return_null(trim_cmd_name));
	}
	else
	{
		cur_dir = getcwd(NULL, 0);
		if (!cur_dir)
			return (NULL);
		trim_cmd_name = ft_substr(cmd_name, 2, ft_strlen(cmd_name) - 2);
		if (!trim_cmd_name)
			return (free_return_null(cur_dir));
		format_path = format_found_path(cur_dir, trim_cmd_name);
		if (!format_path)
		{
			free(cur_dir);
			return (free_return_null(trim_cmd_name));
		}
	}
	return (format_path);
}

char	*search_path(t_list *begin_env, char *cmd_name)
{
	char *full_path;

	if (cmd_name[0] == '/' || cmd_name[0] == '.' || cmd_name[0] == '~')
		full_path = search_path_absolute(begin_env, cmd_name);
	else
		full_path = search_path_relative(begin_env, cmd_name);
	return (full_path);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 16:27:52 by lsoulier          #+#    #+#             */
/*   Updated: 2021/01/06 16:28:03 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*search_path_absolute_home(t_list *begin_env, char *input_path)
{
	t_var	*home;
	char	*trim_cmd_name;
	char	*format_path;

	format_path = NULL;
	home = get_env_var(begin_env, "HOME");
	if (!home)
		return (NULL);
	trim_cmd_name = ft_substr(input_path, 2, ft_strlen(input_path) - 2);
	if (!trim_cmd_name)
		return (NULL);
	if (search_in_dir(home->value, trim_cmd_name))
		format_path = format_found_path(home->value, trim_cmd_name);
	free(trim_cmd_name);
	return (format_path);
}

char	*search_path_absolute_dot(t_list *begin_env, char *input_path)
{
	char	*format_path;
	char	*cur_dir;
	char	*trim_cmd_name;

	cur_dir = getcwd(NULL, 0);
	format_path = NULL;
	if (!cur_dir)
		return (NULL);
	trim_cmd_name = ft_substr(input_path, 2, ft_strlen(input_path) - 2);
	if (!trim_cmd_name)
		return (free_return_null(cur_dir));
	if (search_in_dir(cur_dir, trim_cmd_name))
		format_path = format_found_path(cur_dir, trim_cmd_name);
	free(cur_dir);
	free(trim_cmd_name);
	return (format_path);
}

char	*search_path_absolute_std(char *input_path)
{
	char	*trim_cmd_name;
	char 	*trim_path;
	char 	*format_path;

	format_path = NULL;
	trim_cmd_name = ft_strrchr(input_path, '/') + 1;
	trim_path = ft_strndup(input_path,
		ft_strlen(input_path) - ft_strlen(trim_cmd_name));
	if (!trim_path)
		return (NULL);
	if (search_in_dir(trim_path, trim_cmd_name))
		format_path = ft_strdup(input_path);
	free(trim_path);
	return (format_path);
}
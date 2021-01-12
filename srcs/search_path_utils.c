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

int parse_path_and_name_absolute(t_cmd **cmd)
{
	char *path;
	char *cmd_name;

	cmd_name = ft_strdup(ft_strrchr((*cmd)->args[0], '/') + 1);
	if (!cmd_name)
		return (0);
	path = ft_strndup((*cmd)->args[0],
		ft_strlen((*cmd)->args[0]) - ft_strlen(cmd_name));
	if (!path)
		return (free_return_int(cmd_name));
	free((*cmd)->args[0]);
	(*cmd)->path = path;
	(*cmd)->args[0] = cmd_name;
	return (1);
}

int parse_path_and_name_relative(t_cmd **cmd)
{
	char *path;
	char *cmd_name;

	path = ft_strdup("");
	if (!path)
		return (0);
	cmd_name = ft_strdup((*cmd)->args[0]);
	if (!cmd_name)
		return (free_return_int(cmd_name));
	free((*cmd)->args[0]);
	(*cmd)->path = path;
	(*cmd)->args[0] = cmd_name;
	return (1);
}
int	divide_first_arg(char ***args)
{
	char 	**first_split;
	char	**new;

	first_split = ft_split_charset((*args)[0], " \t\r\f\v\n");
	if (!first_split)
		return (0);
	new = ft_double_tab_merge(first_split, (*args + 1));
	if (!new)
		return (ft_double_tab_free(first_split) != NULL);
	ft_double_tab_free(*args);
	ft_double_tab_free(first_split);
	*args = new;
	return (1);
}

int parse_path_and_name(t_cmd **cmd)
{
	if (ft_strchr((*cmd)->args[0], ' '))
		if (!divide_first_arg(&((*cmd)->args)))
			return (0);
	if ((*cmd)->args[0][0] == '/')
	{
		if (!parse_path_and_name_absolute(cmd))
			return (0);
	}
	else
	{
		if (!parse_path_and_name_relative(cmd))
			return (0);
	}
	return (1);
}

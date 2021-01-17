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

int	parse_path_and_name_absolute(t_cmd **cmd)
{
	char	*path;
	char	*cmd_name;
	int		arg_len;

	cmd_name = ft_strrchr((*cmd)->args[0], '/');
	if (cmd_name)
		cmd_name = ft_strdup(ft_strrchr(cmd_name, '/') + 1);
	else
		cmd_name = ft_strdup("");
	if (!cmd_name)
		return (0);
	arg_len = (*cmd)->args[0] ? ft_strlen((*cmd)->args[0]) : 0;
	path = ft_strndup((*cmd)->args[0], arg_len - ft_strlen(cmd_name));
	if (!path)
		return (free_return_int(cmd_name));
	free((*cmd)->args[0]);
	(*cmd)->path = path;
	(*cmd)->args[0] = cmd_name;
	return (1);
}

int	parse_path_and_name_relative(t_cmd **cmd)
{
	char	*path;
	char	*cmd_name;

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

int	parse_path_and_name(t_cmd **cmd)
{
	if ((*cmd)->args[0][0] == '/'
		|| ft_strncmp((*cmd)->args[0], "./", 2) == 0
		|| ft_strncmp((*cmd)->args[0], "../", 3) == 0)
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

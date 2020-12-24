/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                     :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 22:56:47 by lsoulier          #+#    #+#             */
/*   Updated: 2020/12/24 16:17:29 by louise           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_param(char *cmd, char *builtin_name)
{
	char	*param;
	int		builtin_len;

	builtin_len = ft_strlen(builtin_name) + 1;
	param = ft_substr(cmd, builtin_len, ft_strlen(cmd) - builtin_len - 1);
	return (param);
}

int		exec_cd(char *cmd, t_data *msh_data)
{
	ft_putstr("cd is not implemented yet\n");
	return (1);
}

int		exec_echo(char *cmd, t_data *msh_data)
{
	char	*param;
	char	*new_str;
	int		n_option;
	int 	param_offset;

	param = get_param(cmd, "echo");
	if (!param)
		return (0);
	n_option = ft_strnstr(param, "-n ", 3) != NULL;
	param_offset = 0;
	if (n_option)
		param_offset = 3;
	new_str = process_echo(param + param_offset, msh_data);
	free(param);
	if (!new_str)
		return (0);
	n_option ? ft_putstr_fd(new_str, 1) : ft_putendl_fd(new_str, 1);
	free(new_str);
	return (1);
}

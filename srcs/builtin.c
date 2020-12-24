/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bultin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 22:10:20 by lsoulier          #+#    #+#             */
/*   Updated: 2020/12/24 16:29:37 by louise           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int search_cmd(char *cmd, t_data *msh_data)
{
	int		i;
	char	**builtins;

	i = -1;
	builtins = (char *[TOTAL_BUILTINS]){"echo", "cd", "pwd",
		"export", "unset", "env", "exit"};
	while (++i < TOTAL_BUILTINS)
		if (ft_strstr(cmd, builtins[i]) != NULL)
			return (1);
	return (0);
}

int execute_cmd(char *cmd, t_data *msh_data)
{
	int		(*builtin_fct[TOTAL_BUILTINS])(char *cmd, t_data *msh_data);
	char	**builtins;
	int 	i;

	i = -1;
	builtins = (char *[TOTAL_BUILTINS]){"echo", "cd", "pwd",
		"export", "unset", "env", "exit"};
	builtin_fct[ECHO] = &exec_echo;
	builtin_fct[CD] = &exec_cd;
	builtin_fct[PWD] = &exec_pwd;
	builtin_fct[EXPORT] = &exec_export;
	builtin_fct[UNSET] = &exec_unset;
	builtin_fct[ENV] = &exec_env;
	builtin_fct[EXIT] = &exec_exit;
	while (++i < TOTAL_BUILTINS)
	{
		if (ft_strstr(cmd, builtins[i]) != NULL)
		{
			msh_data->last_return = (*builtin_fct[i])(cmd, msh_data);
			return msh_data->last_return;
		}
	}
	return (0);
}

int exec_exit(char *cmd, t_data *msh_data)
{
	msh_data->exit_msh = 1;
	return (1);
}



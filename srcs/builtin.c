/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bultin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 22:10:20 by lsoulier          #+#    #+#             */
/*   Updated: 2020/12/25 22:05:44 by louise           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	search_builtin(char *cmd_name)
{
	int		i;
	char	**builtins;

	i = -1;
	builtins = (char *[TOTAL_BUILTINS]){"echo", "cd", "pwd",
		"export", "unset", "env", "exit"};
	while (++i < TOTAL_BUILTINS)
		if (ft_strstr(cmd_name, builtins[i]) != NULL)
			return (1);
	return (0);
}

int	execute_builtin(t_data *msh_data, t_cmd *cmd)
{
	char	**builtins;
	int		i;
	int		(*builtin_fct[TOTAL_BUILTINS])(t_data *msh_data, t_cmd *cmd);

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
		if (ft_strstr(cmd->name, builtins[i]) != NULL)
		{
			msh_data->last_return = (*builtin_fct[i])(msh_data, cmd);
			return (msh_data->last_return);
		}
	}
	return (0);
}

int	exec_exit(t_data *msh_data, t_cmd *cmd)
{
	msh_data->exit_msh = 1;
	if (cmd->args[1] && ft_isnum(cmd->args[1]))
		msh_data->exit_value = ft_atoi(cmd->args[1]) % 256;
	return (msh_data->exit_value);
}

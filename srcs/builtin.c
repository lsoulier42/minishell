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
		if (ft_strcmp(cmd_name, builtins[i]) == 0)
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
		if (ft_strcmp(cmd->args[0], builtins[i]) == 0)
		{
			msh_data->last_return = (*builtin_fct[i])(msh_data, cmd);
			return (msh_data->last_return);
		}
	}
	return (0);
}

static unsigned long long	exec_exit_atoi_unsigned(char *str)
{
	unsigned long long result;
	int i;

	i = 0;
	result = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] && ft_isdigit(str[i]))
		result = result * 10 + str[i++] - '0';
	return (result);
}

int							exec_exit(t_data *msh_data, t_cmd *cmd)
{
	msh_data->exit_msh = 1;
	ft_putendl_fd("exit", STDERR_FILENO);
	if (!cmd || (cmd != NULL && !cmd->args[1]))
		msh_data->exit_value = msh_data->last_return;
	else
	{
		msh_data->exit_msh = 0;
		msh_data->exit_value = EXIT_FAILURE;
		if (!cmd->args[2])
		{
			msh_data->exit_msh = 1;
			if ((exec_exit_atoi_unsigned(cmd->args[1]) >= LLONG_MAX
				 && ft_strcmp(cmd->args[1], "-9223372036854775808") != 0)
				|| !ft_isnum(cmd->args[1]))
				msh_data->exit_value = exit_error(cmd->args[1], NON_NUMERIC_ARG);
			else
				msh_data->exit_value = ft_atoi(cmd->args[1]) % 256;
		}
		else
			exit_error(NULL, WRONG_NB_ARGS);
	}
	return (msh_data->exit_value);
}

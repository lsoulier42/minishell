/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 20:41:54 by lsoulier          #+#    #+#             */
/*   Updated: 2021/01/10 20:42:01 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execve_error(char *cmd_name, int errno_value)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd_name, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(strerror(errno_value), STDERR_FILENO);
}

int exit_error(char *arg, int error_code)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd("exit: ", STDERR_FILENO);
	if (error_code == NON_NUMERIC_ARG)
	{
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
	}
	if (error_code == WRONG_NB_ARGS)
		ft_putendl_fd("too many arguments", STDERR_FILENO);
	return (BASH_BUILTIN_EXIT_STATUS);
}

void cd_current_dir_error(void)
{
	ft_putstr_fd("cd: error retrieving current directory: ", STDERR_FILENO);
	ft_putstr_fd("getcwd: cannot access parent directories: ", STDERR_FILENO);
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
}

void fork_error(void)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd("fork: ", STDERR_FILENO);
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
}

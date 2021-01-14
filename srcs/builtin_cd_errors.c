/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_errors.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 18:29:33 by lsoulier          #+#    #+#             */
/*   Updated: 2021/01/14 18:29:44 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void cd_current_dir_error(void)
{
	ft_putstr_fd("cd: error retrieving current directory: ", STDERR_FILENO);
	ft_putstr_fd("getcwd: cannot access parent directories: ", STDERR_FILENO);
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
}

void cd_home_unset(void)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putendl_fd("cd: HOME not set", STDERR_FILENO);
}

void cd_dir_not_found(char *arg)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd("cd: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
}

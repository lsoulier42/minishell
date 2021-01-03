/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 01:10:50 by lsoulier          #+#    #+#             */
/*   Updated: 2020/12/31 01:10:59 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	format_error(char *cmd_name, char *arg, int errno_value, char *str)
{
	ft_putstr(cmd_name);
	ft_putstr(": ");
	if (!str)
		ft_putstr(strerror(errno_value));
	else
		ft_putstr(str);
	ft_putstr(": ");
	ft_putendl_fd(arg, 1);
}

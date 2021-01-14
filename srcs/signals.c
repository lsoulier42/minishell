/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 23:04:24 by lsoulier          #+#    #+#             */
/*   Updated: 2021/01/05 23:04:32 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     g_signal_value = 0;

void    ctrlc_handler(int signum)
{
	g_signal_value = signum;
	close(STDIN_FILENO);
}
void	ctrlslash_handler(int signum)
{
	g_signal_value = signum;
}

void 	sigint_read_handler(t_data *msh_data, int *gnl_return)
{
	if (g_signal_value == SIGINT)
	{
		dup(STDOUT_FILENO);
		write(STDOUT_FILENO, "\n", 1);
		msh_data->last_return = EXIT_FAILURE;
		*gnl_return = 1;
	}
}

void 	sigint_exec_handler(t_data *msh_data, int *end_of_command)
{
	if (g_signal_value == SIGINT)
	{
		dup(STDOUT_FILENO);
		write(STDOUT_FILENO, "\n", 1);
		*end_of_command = 1;
		msh_data->last_return = SIGNAL_ERROR + g_signal_value;
		g_signal_value = 0;
	}
}

void sigquit_exec_handler(t_data *msh_data)
{
	if (g_signal_value == SIGQUIT)
	{
		ft_putendl_fd("Quit (core dumped)", STDOUT_FILENO);
		msh_data->last_return = SIGNAL_ERROR + g_signal_value;
		g_signal_value = 0;
	}
}

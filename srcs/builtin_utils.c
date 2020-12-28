/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                     :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 22:56:47 by lsoulier          #+#    #+#             */
/*   Updated: 2020/12/25 22:28:38 by louise           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		exec_cd(t_data *msh_data, t_cmd *cmd)
{
	ft_putstr("cd is not implemented yet\n");
	return (1);
}
/*
int 	exec_echo(t_data *msh_data, t_cmd *cmd)
{
	int		n_option;
	char	*str;
	char 	*str_endl;

	cmd->out->exit_status = 1;
	n_option = cmd->options[0] && cmd->options[0][0] == 'n';
	str = ft_joinstrs(doubletab_len(cmd->params), cmd->params, " ");
	if (!str)
		cmd->out->exit_status = 0;
	if (!n_option)
	{
		str_endl = ft_strjoin(str, "\n");
		if (!str_endl)
			cmd->out->exit_status = 0;
		free(str);
	}
	else
		str_endl = str;
	cmd->out->ouput = str_endl;
	if (cmd->out->ouput)
		ft_putstr(cmd->out->ouput);
	return (cmd->out->exit_status);
}*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 18:05:58 by lsoulier          #+#    #+#             */
/*   Updated: 2020/12/24 18:06:44 by louise           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.c"

void 	init_data(t_data *msh_data, char *envp[])
{
	msh_data->exit_msh = 0;
	msh_data->begin_env = set_env(envp);
	msh_data->last_return = 0;
	msh_data->level = 1;
}

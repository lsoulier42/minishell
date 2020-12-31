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

#include "minishell.h"

void 	init_data(t_data *msh_data)
{
	msh_data->exit_msh = 0;
	msh_data->last_return = 0;
	msh_data->level = 1;
	msh_data->parsed_input = NULL;
	msh_data->begin_errors = NULL;
	msh_data->begin_history = NULL;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 14:30:08 by lsoulier          #+#    #+#             */
/*   Updated: 2020/12/22 14:30:10 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

int main(int argc, char *argv[], char *envp[])
{
	t_data		mshl_data;
	t_list_env	*track;

	mshl_data.begin_env = set_envlist(envp);
	track = mshl_data.begin_env;
	print_env(track);
	env_clear(&mshl_data.begin_env);
	return (0);
}

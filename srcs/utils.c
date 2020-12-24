/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 15:32:19 by lsoulier          #+#    #+#             */
/*   Updated: 2020/12/24 16:23:46 by louise           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	format_prompt(t_list *track_env)
{
	t_var	*env_pwd;
	char	color;

	color = BLUE;
	env_pwd = get_env_var(track_env, "PWD");
	print_color(env_pwd->value, color);
	print_color("?>", color);
}

void	print_color(char *str, char color)
{
	char ansi_color[6];

	ft_strcpy(ansi_color, "\x1b[3xm");
	ansi_color[3] = color;
	ft_putstr(ansi_color);
	ft_putstr(str);
	ft_putstr("\x1b[0m");
}

void 	init_data(t_data *msh_data, char *envp[])
{
	msh_data->exit_msh = 0;
	msh_data->begin_env = set_env(envp);
	msh_data->last_return = 0;
	msh_data->level = 1;
}

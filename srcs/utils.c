/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 15:32:19 by lsoulier          #+#    #+#             */
/*   Updated: 2020/12/24 18:06:44 by louise           ###   ########.fr       */
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

void 		*free_double_tab(char **tab)
{
	int i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
	return (NULL);
}

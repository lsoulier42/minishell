/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 15:32:19 by lsoulier          #+#    #+#             */
/*   Updated: 2020/12/25 22:22:46 by louise           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	format_prompt(t_list *begin_env)
{
	t_var	*env_pwd;
	char	color;

	color = BLUE;
	env_pwd = get_env_var(begin_env, "PWD");
	print_color(env_pwd->value, color);
	print_color("?>", color);
}

void	print_color(char *str, char color)
{
	char	ansi_color[6];

	ft_strcpy(ansi_color, "\x1b[3xm");
	ansi_color[3] = color;
	ft_putstr(ansi_color);
	ft_putstr(str);
	ft_putstr("\x1b[0m");
}

int	doubletab_len(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

char	*ft_strndup(char *str, int n)
{
	int		i;
	int		len;
	char	*new;

	if (n > ft_strlen(str))
		len = ft_strlen(str);
	else
		len = n;
	new = (char*)malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	ft_strlcpy(new, str, len + 1);
	return (new);
}

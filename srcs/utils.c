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

void	format_prompt(void)
{
	char	color;

	color = BLUE;
	print_color("minishell-1.0$ ", color);
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

char *ft_trim_char(char *str, char *charset)
{
	char	*new_str;
	int 	nb_char;
	int 	i;
	int 	j;
	int 	k;

	i = -1;
	j = -1;
	k = 0;
	nb_char = 0;
	while (str[++i])
		if (ft_ischarset(str[i], charset))
			nb_char ++;
	new_str = (char*)ft_calloc(ft_strlen(str) - nb_char + 1, sizeof(char));
	if (!new_str)
		return (NULL);
	while (str[++j])
		if (!ft_ischarset(str[j], charset))
			new_str[k++] = str[j];
	new_str[k] = '\0';
	return (new_str);
}

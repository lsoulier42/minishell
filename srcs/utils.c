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

void format_prompt(t_data *msh_data)
{
	char 	*prompt;
	char 	*name;
	int 	len;
	t_var	*pwd;
	char 	*pwd_value;

	pwd_value = "";
	name = "minishell@";
	pwd = get_env_var(msh_data->begin_env, "PWD");
	if (pwd)
		pwd_value = pwd->value;
	len = ft_strlen(name) + ft_strlen(pwd_value) + 2;
	prompt = (char*)ft_calloc(len + 1, sizeof(char));
	if (prompt)
	{
		ft_strcat(prompt, name);
		ft_strcat(prompt, pwd_value);
		ft_strcat(prompt, "$ ");
		print_color(prompt, YELLOW);
	}
	else
		print_color(name, YELLOW);
	free(prompt);
}

void	print_color(char *str, char color)
{
	char	ansi_color[6];

	ft_strcpy(ansi_color, "\x1b[3xm");
	ansi_color[3] = color;
	ft_putstr_fd(ansi_color, STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd("\x1b[0m", STDERR_FILENO);
}

int	ft_isoperator(char c)
{
	return (c == '|' || c == ';' || c == '>' || c == '<');
}

int	ft_isseparator(char c)
{
	return (ft_isspace(c) || ft_isoperator(c));
}

int	str_has_ws(char *str)
{
	int i;

	i = -1;
	while(str[++i])
		if (ft_isspace(str[i]))
			return (1);
	return (0);
}

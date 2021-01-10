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
	char 	prompt[PROMPT_MAX_SIZE];
	t_var	*user;
	t_var	*pwd;
	char 	*user_value;
	char 	*pwd_value;

	user_value = "";
	pwd_value = "";
	user = get_env_var(msh_data->begin_env, "USER");
	if (user)
		user_value = user->value;
	pwd = get_env_var(msh_data->begin_env, "PWD");
	if (pwd)
		pwd_value = pwd->value;
	if (ft_strlen(user_value)
		+ ft_strlen(pwd_value)
		+ ft_strlen(msh_data->name) + 2 < PROMPT_MAX_SIZE)
	{
		ft_strcpy(prompt, user_value);
		ft_strcat(prompt, "@");
		ft_strcat(prompt, msh_data->name);
		ft_strcat(prompt, pwd_value);
		ft_strcat(prompt, "$ ");
		print_color(prompt, YELLOW);
	}
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

int	doubletab_len(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

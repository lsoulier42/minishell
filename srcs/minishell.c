/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 14:30:08 by lsoulier          #+#    #+#             */
/*   Updated: 2020/12/22 22:51:34 by louise           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

char *format_prompt(t_list_env *track)
{
	char *env_pwd;
	char *new_path;

	env_pwd = get_env_value(track, "PWD");
	new_path = ft_strjoin(env_pwd, "?>");
	return (new_path);
}

void print_blue(char *str)
{
	ft_putstr("\x1b[34m");
	ft_putstr(str);
	ft_putstr("\x1b[0m");
}

int main(int argc, char *argv[], char *envp[])
{
	t_data		mshl_data;
	char 		buffer[BUFFER_SIZE + 1];
	char 		*prompt;
	int 		read_return;

	mshl_data.exit_mshl = 0;
	mshl_data.begin_env = set_envlist(envp);
	while(!mshl_data.exit_mshl)
	{
		prompt = format_prompt(mshl_data.begin_env);
		print_blue(prompt);
		free(prompt);
		ft_bzero(buffer, BUFFER_SIZE + 1);
		while ((read_return = read(0, buffer, BUFFER_SIZE)) != 0)
		{
			buffer[read_return] = '\0';
			if (search_cmd(buffer))
				execute_cmd(buffer, &mshl_data);
			else
				ft_putstr("Command not found.\n");
			if (buffer[read_return - 1] == '\n')
				break ;
		}
	}
	env_clear(&mshl_data.begin_env);
	return (0);
}

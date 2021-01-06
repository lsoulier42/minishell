/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 14:30:08 by lsoulier          #+#    #+#             */
/*   Updated: 2020/12/25 21:59:56 by louise           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

static int	init_data(t_data *msh_data, char *msh_name, char *envp[])
{
	msh_data->exit_msh = 0;
	msh_data->last_return = EXIT_SUCCESS;
	msh_data->parsed_input = NULL;
	msh_data->begin_env = set_env(envp);
	if (ft_strncmp(msh_name, "./", 2) == 0)
	{
		msh_data->name = ft_substr(msh_name, 2, ft_strlen(msh_name) - 2);
		if (!msh_data->name)
			return (0);
	}
	else
	{
		msh_data->name = ft_strdup(msh_name);
		if (!msh_data->name)
			return (0);
	}
	msh_data->exit_value = EXIT_SUCCESS;
	return (1);
}

static int	msh_second_loop(t_data *msh_data,
	char *buffer, int argc, char **argv)
{
	int error;

	error = 0;
	msh_data->parsed_input = parse_input(buffer);
	if (msh_data->parsed_input)
	{
		if (argc == 2 && ft_strcmp(argv[1], "debug") == 0)
			print_instructions_list(msh_data->parsed_input->begin_instructions);
		else
		{
			if (!execute_all_cmds(msh_data))
				error = 1;
		}
		del_user_input(msh_data->parsed_input);
	}
	else
		error = 1;
	return (error == 0);
}

static int	msh_first_loop(t_data *msh_data,
	int argc, char **argv, int *read_return)
{
	char		buffer[BUFFER_SIZE + 1];
	int			end_of_command;
	int			error;

	format_prompt(msh_data);
	ft_bzero(buffer, BUFFER_SIZE + 1);
	end_of_command = 0;
	g_signal_value = 0;
	error = 0;
	while (!end_of_command)
	{
		*read_return = read(0, buffer, BUFFER_SIZE);
		sigint_read_handler(read_return);
		if (*read_return <= 0 || g_signal_value == SIGINT)
			break ;
		buffer[*read_return] = '\0';
		if (!msh_second_loop(msh_data, buffer, argc, argv))
			error = 1;
		sigint_exec_handler(&end_of_command);
		if (buffer[*read_return - 1] == '\n' || error == 1)
			end_of_command = 1;
	}
	return (error == 0);
}

int			main(int argc, char *argv[], char *envp[])
{
	t_data		msh_data;
	int			read_return;
	int			error;

	if (!init_data(&msh_data, argv[0], envp))
		return (EXIT_FAILURE);
	read_return = 1;
	error = 0;
	signal(SIGINT, ctrlc_handler);
	signal(SIGQUIT, ctrlslash_handler);
	while (!msh_data.exit_msh && read_return > 0)
		if (!msh_first_loop(&msh_data, argc, argv, &read_return))
			error = 1;
	ft_putendl_fd("exit", STDOUT_FILENO);
	ft_lstclear(&(msh_data.begin_env), &del_var);
	free(msh_data.name);
	if (error == 1)
		msh_data.exit_value = EXIT_FAILURE;
	return (msh_data.exit_value);
}

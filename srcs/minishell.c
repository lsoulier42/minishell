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

static int	init_data(t_data *msh_data, char *envp[])
{
	msh_data->exit_msh = 0;
	msh_data->last_return = EXIT_SUCCESS;
	msh_data->parsed_input = NULL;
	msh_data->begin_env = set_env(envp);
	if (!msh_data->begin_env)
		return (0);
	msh_data->exit_value = EXIT_SUCCESS;
	return (1);
}

static int	msh_second_loop(t_data *msh_data,
	char *line, int argc, char **argv)
{
	msh_data->parsed_input = parse_input(line);
	if (msh_data->parsed_input)
	{
		if (argc == 2 && ft_strcmp(argv[1], "debug") == 0)
			print_instructions_list(msh_data->parsed_input->begin_instructions);
		else
		{
			if (!execute_all_cmds(msh_data))
				exit(EXIT_FAILURE);
		}
		del_user_input(msh_data->parsed_input);
	}
	else
		msh_data->last_return = PARSING_ERROR;
	return (EXIT_SUCCESS);
}

static int	msh_first_loop(t_data *msh_data,
	int argc, char **argv, int *gnl_return)
{
	int			end_of_command;
	int			error;
	char 		*line;

	format_prompt(msh_data);
	end_of_command = 0;
	g_signal_value = 0;
	error = 0;
	while (!end_of_command)
	{
		*gnl_return = get_next_line(STDIN_FILENO, &line);
		sigint_read_handler(msh_data, gnl_return);
		if (*gnl_return == -1 || g_signal_value == SIGINT)
			break ;
		if (msh_second_loop(msh_data, line, argc, argv) == EXIT_FAILURE)
			error = 1;
		free(line);
		sigint_exec_handler(msh_data, &end_of_command);
		if (*gnl_return == 1 || error == 1)
			end_of_command = 1;
	}
	return (error == 0);
}

int			main(int argc, char *argv[], char *envp[])
{
	t_data		msh_data;
	int			gnl_return;

	if (!init_data(&msh_data, envp))
		return (EXIT_FAILURE);
	gnl_return = 1;
	if (signal(SIGINT, ctrlc_handler) == SIG_ERR)
		exit(EXIT_FAILURE);
	if (signal(SIGQUIT, ctrlslash_handler) == SIG_ERR)
		exit(EXIT_FAILURE);
	while (!msh_data.exit_msh && gnl_return > 0)
		if (!msh_first_loop(&msh_data, argc, argv, &gnl_return))
			break ;
	if (msh_data.exit_msh != 1)
		exec_exit(&msh_data, NULL);
	ft_lstclear(&(msh_data.begin_env), &del_var);
	return (msh_data.exit_value);
}

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

static int	init_data(t_data *msh_data, char *envp[])
{
	msh_data->exit_msh = 0;
	msh_data->last_return = EXIT_SUCCESS;
	msh_data->parsed_input = NULL;
	msh_data->exit_value = EXIT_SUCCESS;
	msh_data->begin_env = set_env(envp);
	if (!msh_data->begin_env)
		return (0);
	return (1);
}

static int	msh_third_loop(t_data *msh_data, char *line)
{
	int error;

	error = 0;
	msh_data->parsed_input = parse_input(msh_data, line);
	if (msh_data->parsed_input)
	{
		if (!execute_all_cmds(msh_data))
			error = 1;
		del_user_input(msh_data->parsed_input);
	}
	else
		msh_data->last_return = PARSING_ERROR;
	return (error == 0);
}

static int	msh_second_loop(t_data *msh_data, int *gnl_return,
	char **line, int *end_of_command)
{
	*gnl_return = get_next_line(STDIN_FILENO, line);
	sigint_read_handler(msh_data, gnl_return);
	if (*gnl_return == -1
		|| (*gnl_return == 0 && *line && ft_strcmp(*line, "") == 0)
		|| g_signal_value == SIGINT)
		return (-1);
	if (*gnl_return == 1)
	{
		if (!msh_third_loop(msh_data, *line))
			return (0);
		sigint_exec_handler(msh_data, end_of_command);
		if (*gnl_return == 1)
			*end_of_command = 1;
	}
	return (1);
}

static int	msh_first_loop(t_data *msh_data, int *gnl_return)
{
	int			end_of_command;
	int			error;
	char		*line;
	int			loop_return;

	format_prompt(msh_data);
	end_of_command = 0;
	g_signal_value = 0;
	error = 0;
	line = NULL;
	while (!end_of_command)
	{
		loop_return = msh_second_loop(msh_data,
			gnl_return, &line, &end_of_command);
		if (loop_return == -1)
			break ;
		if (loop_return == 0)
		{
			error = 1;
			break ;
		}
	}
	if (line)
		free(line);
	return (error == 0);
}

int			main(int argc, char *argv[], char *envp[])
{
	t_data		msh_data;
	int			gnl_return;

	(void)argc;
	if (ft_strcmp(argv[0], "./minishell") == 0)
		argv[1] = "fake";
	if (!init_data(&msh_data, envp))
		return (EXIT_FAILURE);
	gnl_return = 1;
	if (signal(SIGINT, ctrlc_handler) == SIG_ERR)
		exit(EXIT_FAILURE);
	if (signal(SIGQUIT, ctrlslash_handler) == SIG_ERR)
		exit(EXIT_FAILURE);
	while (!msh_data.exit_msh && gnl_return > 0)
		if (!msh_first_loop(&msh_data, &gnl_return))
			break ;
	if (msh_data.exit_msh != 1)
		exec_exit(&msh_data, NULL);
	ft_lstclear(&(msh_data.begin_env), &del_var);
	return (msh_data.exit_value);
}

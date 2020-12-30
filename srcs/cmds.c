/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 18:04:49 by lsoulier          #+#    #+#             */
/*   Updated: 2020/12/26 02:39:44 by louise           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int 	create_args_tab(char ***args, t_list *tokens)
{
	int i;

	i = 0;
	while (tokens)
	{
		(*args)[i] = sub_quote(get_token_value(tokens));
		if (!(*args)[i])
			return (0);
		i++;
		tokens = tokens->next;
	}
	(*args)[i] = NULL;
	return (1);
}

int 	parse_one_pipe_cmds(t_list **tokens, t_redirection *redirection)
{
	t_list	*cmd_el;
	t_list	*track;
	char	*name;
	char	**args;

	track = *tokens;
	name = sub_quote(get_token_value(track));
	if (!name)
		return (0);
	track = track->next;
	args = (char**)malloc(sizeof(char*) * (ft_lstsize(track) + 1));
	if (!args)
		return (free_str_return_int(name));
	if (!create_args_tab(&args, track))
		return (free_cmd_tabs(name, args));
	cmd_el = new_cmd_el(name, args, redirection);
	if (!cmd_el)
		return (free_cmd_tabs(name, args));
	*tokens = cmd_el;
	return (1);
}

int 	parse_cmds(t_list *instructions)
{
	t_list			*pipes;
	t_list 			**begin_cmds;
	t_redirection	*redirection;

	while (instructions)
	{
		pipes = get_instruction_pipes(instructions);
		while (pipes)
		{
			begin_cmds = &(((t_pipe*)(pipes->content))->begin_cmds);
			redirection = parse_redirections(*begin_cmds);
			if (!redirection)
				return (0);
			if(!parse_one_pipe_cmds(begin_cmds, redirection))
				return (0);
			pipes = pipes->next;
		}
		instructions = instructions->next;
	}
	return (1);
}

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

char **create_args_tab(t_list *tokens)
{
	int		i;
	char	**args;

	args = (char**)malloc(sizeof(char*) * (ft_lstsize(tokens) + 1));
	if (!args)
		return (NULL);
	i = 0;
	while (tokens)
	{
		args[i] = ft_strdup(get_token_value(tokens));
		if (!args[i])
			return (ft_free_double_tab(args));
		i++;
		tokens = tokens->next;
	}
	args[i] = NULL;
	return (args);
}

int		parse_one_pipe_cmds(t_list **tokens, t_redirection **redirections)
{
	t_list	*cmd_el;
	char	**args;

	args = create_args_tab(*tokens);
	if (!args)
		return (0);
	cmd_el = new_cmd_el(doubletab_len(args), args, redirections);
	if (!cmd_el)
		return (free_double_tab_ret_int(args));
	ft_lstclear(tokens, &del_token);
	*tokens = cmd_el;
	return (1);
}

int		parse_cmds(t_list *instructions)
{
	t_list			*pipes;
	t_list			**begin_cmds;
	t_redirection	**redirections;

	while (instructions)
	{
		pipes = get_instruction_pipes(instructions);
		while (pipes)
		{
			begin_cmds = &(((t_pipe*)(pipes->content))->begin_cmds);
			redirections = parse_redirections(*begin_cmds);
			if (!redirections)
				return (0);
			if (!parse_one_pipe_cmds(begin_cmds, redirections))
				return (0);
			pipes = pipes->next;
		}
		instructions = instructions->next;
	}
	return (1);
}

t_cmd	*get_cmd(t_list *pipe_el)
{
	t_list	*cmds;
	t_cmd	*cmd;

	cmds = get_pipes_cmds(pipe_el);
	cmd = (t_cmd*)cmds->content;
	return (cmd);
}

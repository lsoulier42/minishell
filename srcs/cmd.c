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

int 		is_semicolon(t_instruction *it)
{
	if (!it)
		return (0);
	return(ft_strcmp(it->value, ";") == 0 && !it->is_quote);
}

int 		add_param(t_list **begin, char *str)
{
	char	*param_str;
	t_list	*param_el;

	param_str = ft_strdup(str);
	if (!param_str)
		return (0);
	param_el = ft_lstnew(param_str);
	if (!param_el)
		return (0);
	ft_lstadd_back(begin, param_el);
	return (1);
}

t_list		*create_cmd(t_list *instruct)
{
	t_cmd			*cmd;
	t_instruction	*current;
	int 			index;

	cmd = (t_cmd*)malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	index = 0;
	cmd->params = NULL;
	while (instruct)
	{
		current = (t_instruction*)instruct->content;
		if (is_semicolon(current))
			break ;
		if (index++ == 0)
		{
			if (!(cmd->name = ft_strdup(current->value)))
				return (NULL);
		}
		else
			if (!add_param(&cmd->params, current->value))
				return (NULL);
		instruct = instruct->next;
	}
	return (ft_lstnew(cmd));
}

int 	recreate_cmds(t_list **begin_cmds)
{
	t_instruction	*current;
	t_instruction	*previous;
	t_list			*track;
	t_list			*begin;
	t_list			*el;

	begin = NULL;
	previous = NULL;
	track = *begin_cmds;
	while (track)
	{
		current = (t_instruction*)track->content;
		if ((previous == NULL || is_semicolon(previous)) && !is_semicolon(current))
		{
			if(!(el = create_cmd(track)))
				return (0);
			ft_lstadd_back(&begin, el);
		}
		track = track->next;
	}
	ft_lstclear(begin_cmds, &del_instruction);
	*begin_cmds = begin;
	return (1);
}

int 	split_cmds(t_list *pipes)
{
	t_pipe			*current;

	while (pipes)
	{
		current = (t_pipe*)pipes->content;
		if(!recreate_cmds(&current->begin_cmd))
			return (0);
		pipes = pipes->next;
	}
	return (1);
}


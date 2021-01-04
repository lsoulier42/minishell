/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 02:56:32 by lsoulier          #+#    #+#             */
/*   Updated: 2020/12/29 02:56:44 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*new_cmd(char *name, char **args, t_redirection **redirections)
{
	t_cmd	*new;

	new = (t_cmd*)malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->name = name;
	new->args = args;
	new->redirections = redirections;
	new->is_last = 0;
	return (new);
}

t_list	*new_cmd_el(char *name, char **args, t_redirection **redirections)
{
	t_list	*el;
	t_cmd	*cmd;

	cmd = new_cmd(name, args, redirections);
	if (!cmd)
		return (NULL);
	el = ft_lstnew(cmd);
	return (el);
}

void 	del_cmd(void *cmd_void)
{
	t_cmd	*cmd;

	cmd = (t_cmd*)cmd_void;
	free(cmd->name);
	free_double_tab(cmd->args);
	del_redirection(cmd->redirections[IN]);
	del_redirection(cmd->redirections[OUT]);
	free(cmd->redirections);
	free(cmd_void);
}

int 	free_cmd_tabs(char *name, char **args)
{
	free(name);
	free_double_tab(args);
	return (0);
}

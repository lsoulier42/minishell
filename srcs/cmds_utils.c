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

t_cmd	*new_cmd(int argc, char **args, t_redirection **redirections)
{
	t_cmd	*new;

	new = (t_cmd*)malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->path = NULL;
	new->argc = argc;
	new->args = args;
	new->redirections = redirections;
	new->is_last = 0;
	new->is_piped = 0;
	return (new);
}

t_list	*new_cmd_el(int argc, char **args, t_redirection **redirections)
{
	t_list	*el;
	t_cmd	*cmd;

	cmd = new_cmd(argc, args, redirections);
	if (!cmd)
		return (NULL);
	el = ft_lstnew(cmd);
	return (el);
}

void	del_cmd(void *cmd_void)
{
	t_cmd	*cmd;

	cmd = (t_cmd*)cmd_void;
	if (cmd->path)
		free(cmd->path);
	if (cmd->args)
		ft_double_tab_free(cmd->args);
	del_redirection(cmd->redirections[IN]);
	del_redirection(cmd->redirections[OUT]);
	free(cmd->redirections);
	free(cmd_void);
}

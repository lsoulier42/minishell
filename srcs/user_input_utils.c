/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_input_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 02:46:35 by lsoulier          #+#    #+#             */
/*   Updated: 2020/12/29 02:46:41 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*error_tokens(t_user_input *new)
{
	free(new->input);
	free(new);
	return (NULL);
}

void	*error_instructions(t_user_input *new, t_list **tokens)
{
	ft_lstclear(tokens, &del_token);
	return (error_tokens(new));
}

void	*error_pipes(t_user_input *new, t_list **tokens)
{
	del_instruction_list(&(new->begin_instructions));
	return (error_instructions(new, tokens));
}

void	*error_cmds(t_user_input *new, t_list **tokens)
{
	t_list	*el;
	t_list	*pipes;

	el = new->begin_instructions;
	while (el)
	{
		pipes = get_instruction_pipes(el);
		ft_lstclear(&pipes, &del_pipe);
		el = el->next;
	}
	return (error_pipes(new, tokens));
}

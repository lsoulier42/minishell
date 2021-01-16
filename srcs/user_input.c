/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 18:05:33 by lsoulier          #+#    #+#             */
/*   Updated: 2020/12/26 02:39:44 by louise           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_user_input	*parse_input(char *buffer)
{
	t_user_input	*new;
	t_list			*begin_tokens;

	if (!buffer)
		return (0);
	new = (t_user_input*)malloc(sizeof(t_user_input));
	if (!new)
		return (NULL);
	new->input = ft_strdup(buffer);
	if (!new->input)
		return (free_return_null(new));
	begin_tokens = lexer(new->input, 0);
	if (!begin_tokens)
		return (error_tokens(new));
	new->begin_instructions = parse_instructions(begin_tokens);
	if (!new->begin_instructions)
		return (error_cmds(new, new->begin_instructions));
	if (!parse_pipes(new->begin_instructions))
		return (error_cmds(new, new->begin_instructions));
	if (!parse_cmds(new->begin_instructions))
		return (error_cmds(new, new->begin_instructions));
	return (new);
}

void			del_user_input(t_user_input *input)
{
	ft_lstclear(&(input->begin_instructions), &del_instruction);
	free(input->input);
	free(input);
}

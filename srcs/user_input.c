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

	new = (t_user_input*)malloc(sizeof(t_user_input));
	if (!new)
		return (NULL);
	new->input = ft_strdup(buffer);
	if (!new->input)
		return (free_return_null(new));
	begin_tokens = split_tokens(new->input);
	if (!begin_tokens)
		return (error_tokens(new));
	new->begin_instructions = parse_instructions(begin_tokens);
	if (!new->begin_instructions)
		return (error_instructions(new, &begin_tokens));
	if (!parse_pipes(new->begin_instructions))
		return (error_pipes(new, &begin_tokens));
	if (!parse_cmds(new->begin_instructions))
		return (error_cmds(new, &begin_tokens));
	return (new);
}

void	del_user_input(t_user_input *input)
{
	ft_lstclear(&(input->begin_instructions), &del_instruction);
	free(input->input);
	free(input);
}

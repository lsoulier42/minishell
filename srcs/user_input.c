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

#include "minishell.c"

t_user_input *parse_input(t_data *msh_data, char *buffer)
{
	t_user_input *new;

	new = (t_user_input*)malloc(sizeof(t_user_input));
	if (!new)
		return (NULL);
	new->begin_instructions = split_instructions(buffer);
	if (!new->begin_instructions)
		return (NULL);
	new->begin_pipes = split_pipes(new->begin_instructions);
	if (!split_cmds(new->begin_pipes))
		return (NULL);
	ft_lstclear(&new->begin_instructions, &del_instruction);
}
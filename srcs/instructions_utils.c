/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 00:27:11 by lsoulier          #+#    #+#             */
/*   Updated: 2020/12/27 14:21:59 by louise           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.c"

t_instruction	*create_instruction(char *str, int is_quote)
{
	t_instruction *new;

	new = (t_instruction*)malloc(sizeof(t_instruction));
	if (!new)
		return (NULL);
	new->value = ft_strdup(str);
	if (!new->value)
	{
		free(new);
		return (NULL);
	}
	new->is_quote = is_quote;
	return (new);
}

void 	del_instruction(void *del_void)
{
	t_instruction *del;

	del = (t_instruction*)del_void;
	free(del->value);
	free(del);
}

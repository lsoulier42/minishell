/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 21:47:45 by lsoulier          #+#    #+#             */
/*   Updated: 2021/01/10 21:47:54 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int expand_one_arg_finish(char **arg_ptr, t_list **begin, char buffer[BUFFER_SIZE + 1], int *j)
{
	if (!flush_buffer(begin, buffer, j))
		return (0);
	free(*arg_ptr);
	*arg_ptr = ft_lstjoin(*begin);
	ft_lstclear(begin, &free);
	return (1);
}

int	expand_one_arg(t_data *msh_data, char **arg_ptr)
{
	char	quote_char;
	char	buffer[BUFFER_SIZE + 1];
	int		i;
	int 	j;
	t_list	*begin;

	expand_init_var(&i, &j, &quote_char, &begin);
	while ((*arg_ptr)[++i])
	{
		if (expand_is_flushable_buffer(*arg_ptr, i, j, quote_char))
			if(!flush_buffer(&begin, buffer, &j))
				return (0);
		if (expand_is_printable(*arg_ptr, i, quote_char))
			buffer[j++] = (*arg_ptr)[i];
		quote_char = expand_set_quote_char(quote_char, *arg_ptr, i);
		if (expand_is_expandable_var(*arg_ptr, i, quote_char))
			if (!expand_one_var(msh_data, &begin, *arg_ptr, &i))
				return (0);
		if (expand_is_last_return_var(*arg_ptr, i, quote_char))
			if (!expand_last_return(msh_data, &begin, &i))
				return (0);
	}
	if (!expand_one_arg_finish(arg_ptr, &begin, buffer, &j))
		return (0);
	return (1);
}

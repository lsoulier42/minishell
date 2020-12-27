/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 00:26:12 by lsoulier          #+#    #+#             */
/*   Updated: 2020/12/27 14:29:48 by louise           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.c"

t_list			*create_instruction_el(char *str, int is_quote)
{
	t_list			*el;
	t_instruction	*new;

	new = create_instruction(str, is_quote);
	el = ft_lstnew(new);
	if (!el)
	{
		del_instruction(new);
		return (NULL);
	}
	return (el);
}

int				add_instruct_std(t_list **begin, char **str)
{
	t_list	*el;
	char 	*new;
	int		len;

	len = 0;
	while (*str[len] && !quote_char(*str[len]) && !ft_isspace(*str[len]))
		len++;
	new = ft_strndup(*str, len);
	if (!new)
		return (0);
	el = create_instruction_el(new, 0);
	if (!el)
	{
		free(new);
		return (0);
	}
	ft_lstadd_back(begin, el);
	*str += len;
	return (0);
}

void 			*del_str_temp(char *str)
{
	free(str);
	return (NULL);
}

t_list			*split_instructions(char *buffer)
{
	t_list	*begin;
	char	*str;
	char 	*str_begin;

	begin = NULL;
	str = ft_strdup(buffer);
	str_begin = str;
	while (*str)
	{
		if (quote_char(*str))
		{
			if (!add_instruct_quote(&begin, &str))
				return (del_str_temp(str_begin));
		}
		else if (!ft_isspace(*str))
			if (!add_instruct_std(&begin, &str))
				return (del_str_temp(str_begin));
	}
	del_str_temp(str_begin);
	return (begin);
}

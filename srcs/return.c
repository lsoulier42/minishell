/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 18:04:31 by lsoulier          #+#    #+#             */
/*   Updated: 2020/12/24 18:18:15 by louise           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.c"

void		set_return(t_return *ret, char *output, int exit_status)
{
	ret->ouput = output;
	ret->exit_status = exit_status;
}

t_return	*new_return(char *output, int exit_status)
{
	t_return *new;

	new = (t_return*)malloc(sizeof(t_return));
	if (new)
		set_return(new, output, exit_status);
	return (new);
}

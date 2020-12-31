/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 01:10:50 by lsoulier          #+#    #+#             */
/*   Updated: 2020/12/31 01:10:59 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_error	*new_error(char *str_error, char *process, char *arg, int code)
{
	t_error	*new;

	new = (t_error*)malloc(sizeof(t_error));
	if (!new)
		return (NULL);
	new->str_error = str_error;
	new->process = process;
	new->arg = arg;
	new->code = code;
	return (new);
}

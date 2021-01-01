/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 03:25:17 by lsoulier          #+#    #+#             */
/*   Updated: 2020/12/31 03:25:24 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	change_env_var_value(char *key, char *new_value)
{
	t_var	*var;
	char	**value_ref;

	var = get_env_var(key);
	if (!var)
		return (0);
	value_ref = &(var->value);
	free(var->value);
	*value_ref = new_value;
	return (1);
}

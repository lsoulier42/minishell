/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 14:09:16 by lsoulier          #+#    #+#             */
/*   Updated: 2020/12/24 14:32:11 by louise           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_var(void *var)
{
	t_var	*var_cast;

	var_cast = (t_var*)var;
	free(var_cast->key);
	free(var_cast->value);
	free(var);
}

t_var	*new_var(char *key, char *value)
{
	t_var	*new;

	new = (t_var*)malloc(sizeof(t_var));
	if (!new)
		return (NULL);
	new->key = key;
	new->value = value;
	return (new);
}

int parse_var(char *unparsed, char **key, char **value)
{
	if (unparsed[0] == '=')
	{
		*key = ft_strdup("=");
		*value = ft_strdup("");
	}
	else if (unparsed_var_has_equal(unparsed))
	{
		*key = parse_var_key(unparsed);
		*value = parse_var_value(unparsed);
	}
	else
	{
		*key = ft_strdup(unparsed);
		*value = ft_strdup("");
	}
	if (!(*key) || !(*value))
	{
		if (*key)
			free(*key);
		if (*value)
			free(*value);
		return (0);
	}
	return (1);
}

int	cmp_key_var(void *var1_void, void *var2_void)
{
	t_var	*var1;
	t_var	*var2;

	var1 = (t_var*)var1_void;
	var2 = (t_var*)var2_void;
	return (ft_strcmp(var1->key, var2->key));
}

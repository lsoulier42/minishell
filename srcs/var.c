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

void 		set_var(t_var *new_var, char *key, char *value)
{
	new_var->key = key;
	new_var->value = value;
}

void 		del_var(void *var)
{
	t_var *var_cast;

	var_cast = (t_var*)var;
	free(var_cast->key);
	free(var_cast->value);
}

t_var		*parse_var(char *str)
{
	t_var	*new_var;
	int 	index;
	int 	str_len;

	index = 0;
	str_len = ft_strlen(str);
	new_var = (t_var*)malloc(sizeof(t_var));
	if (new_var)
	{
		while (str[index] && str[index] != '=')
			index++;
		new_var->key = (char*)malloc(sizeof(char) * (index + 1));
		new_var->value = (char*)malloc(sizeof(char) * (str_len - index));
		if (!new_var->key || !new_var->value)
			return (NULL);
		ft_strlcpy(new_var->key, str, index + 1);
		ft_strlcpy(new_var->value, str + index + 1, str_len - index);
	}
	return (new_var);
}

int cmp_key_var(t_var *var1, t_var *var2)
{
	return (ft_strcmp(var1->key, var2->key));
}

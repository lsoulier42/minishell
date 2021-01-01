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

char	*parse_var_key(char *unparsed)
{
	char	*key;
	int		i;

	i = 0;
	while (unparsed[i] && unparsed[i] != '=')
		i++;
	if (unparsed[i] != '=')
		return (NULL);
	key = (char*)malloc(sizeof(char) * (i + 1));
	if (!key)
		return (NULL);
	ft_strlcpy(key, unparsed, i + 1);
	return (key);
}

char	*parse_var_value(char *unparsed)
{
	char	*value;
	int		i;
	int		len;

	i = 0;
	while (unparsed[i] && unparsed[i] != '=')
		i++;
	if (unparsed[i] != '=')
		return (NULL);
	len = ft_strlen(unparsed) - i - 1;
	value = (char*)malloc(sizeof(char) * (len + 1));
	if (!value)
		return (NULL);
	ft_strlcpy(value, unparsed + i + 1, len + 1);
	return (value);
}

t_var	*parse_var(char *unparsed)
{
	t_var	*new_var;

	new_var = (t_var*)malloc(sizeof(t_var));
	if (new_var)
	{
		new_var->key = parse_var_key(unparsed);
		if (!new_var->key)
			return (free_return_null(new_var));
		new_var->value = parse_var_value(unparsed);
		if (!new_var->value)
		{
			free(new_var->key);
			return (free_return_null(new_var));
		}
	}
	return (new_var);
}

int	cmp_key_var(void *var1_void, void *var2_void)
{
	t_var	*var1;
	t_var	*var2;

	var1 = (t_var*)var1_void;
	var2 = (t_var*)var2_void;
	return (ft_strcmp(var1->key, var2->key));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 17:00:36 by lsoulier          #+#    #+#             */
/*   Updated: 2021/01/11 17:00:43 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		var_has_equal(char *str)
{
	int	i;

	i = -1;
	if (str[0] == '=')
	{
		invalid_identifier("export", str);
		return (-1);
	}
	while (str[++i])
		if (str[i] == '=')
			return (1);
	return (0);
}

int		var_has_plus(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '+')
	{
		invalid_identifier("export", str);
		return (-1);
	}
	while (str[i] && str[i] != '+')
		i++;
	if (str[i] == '\0')
		return (0);
	if (str[i] == '+' && str[i + 1] != '=')
		return (-1);
	else
		return (1);
}

char	*get_export_key(char *unparsed)
{
	int	i;

	i = 0;
	if (ft_isdigit(unparsed[0]) || unparsed[0] == '+' || unparsed[0] == '=')
	{
		invalid_identifier("export", unparsed);
		return (NULL);
	}
	while (unparsed[i] && (ft_isalnum(unparsed[i]) || unparsed[i] == '_'))
		i++;
	if (unparsed[i] != '\0' && unparsed[i] != '+' && unparsed[i] != '=')
	{
		invalid_identifier("export", unparsed);
		return (NULL);
	}
	return (ft_strndup(unparsed, i));
}

int		get_export_value(char *unparsed, int has_equal, char **value)
{
	int		i;
	char	*new;

	i = 0;
	if (!has_equal)
		return (1);
	while (unparsed[i] && unparsed[i] != '=')
		i++;
	new = ft_strdup(unparsed + i + 1);
	if (!new)
		return (0);
	*value = new;
	return (1);
}

int		del_export_var(t_export_var *var)
{
	if (var->key)
		free(var->key);
	if (var->value)
		free(var->value);
	return (0);
}

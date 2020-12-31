/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 18:29:41 by lsoulier          #+#    #+#             */
/*   Updated: 2020/12/30 18:29:49 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char 	*get_cmd_next_value(char *str, int *len)
{
	char	*key;
	t_var	*var;
	char 	*value;

	if (ft_isdigit(str[0]))
	{
		*len = 1;
		return (ft_strdup(""));
	}
	else
		while (str[*len] && (ft_isalnum(str[*len]) || str[*len] == '_'))
			*len += 1;
	key = ft_strndup(str, *len);
	if (!key)
		return (NULL);
	var = get_env_var(key);
	if (!var)
		value = ft_strdup("");
	else
		value = ft_strdup(var->value);
	free(key);
	return (value);
}

int		expand_one_var(char **cur_arg, int *index)
{
	int 	key_len;
	char	*var_value;
	char 	*new_cur_arg;

	key_len = 0;
	var_value = get_cmd_next_value(*cur_arg + *index + 1, &key_len);
	if (!var_value)
		return (0);
	new_cur_arg = (char*)ft_calloc(ft_strlen(*cur_arg)
								   - key_len + ft_strlen(var_value), sizeof(char));
	if (!new_cur_arg)
		return (free_return_int(var_value));
	ft_strlcpy(new_cur_arg, *cur_arg, *index + 1);
	ft_strcat(new_cur_arg, var_value);
	ft_strcat(new_cur_arg, *cur_arg + *index + key_len + 1);
	free(*cur_arg);
	*index += ft_strlen(var_value);
	free(var_value);
	*cur_arg = new_cur_arg;
	return (1);
}

int		expand_last_return(t_data msh_data, char **cur_arg, int *index)
{
	char	*itoa_value;
	int 	itoa_len;
	char 	*new_cur_arg;

	itoa_value = ft_itoa(msh_data.last_return);
	if (!itoa_value)
		return (0);
	itoa_len = ft_strlen(itoa_value);
	new_cur_arg = (char*)ft_calloc(ft_strlen(*cur_arg) + itoa_len - 1, sizeof(char));
	if (!new_cur_arg)
		return (free_return_int(itoa_value));
	ft_strlcpy(new_cur_arg, *cur_arg, *index + 1);
	ft_strcat(new_cur_arg, itoa_value);
	ft_strcat(new_cur_arg, *cur_arg + *index + 3);
	free(*cur_arg);
	*index += itoa_len;
	free(itoa_value);
	*cur_arg = new_cur_arg;
	return (1);
}

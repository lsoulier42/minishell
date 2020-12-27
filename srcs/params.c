/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 19:28:10 by lsoulier          #+#    #+#             */
/*   Updated: 2020/12/27 12:39:10 by louise           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		parse_params(t_data *msh_data, t_list *params)
{
	t_list *env;

	env = msh_data->begin_env;
	if (!sub_var(env, params))
		return (0);
	if (!sub_interrogation(msh_data, params))
		return (0);
	if (!sub_absent_key(params))
		return (0);
	return (1);
}

int 	check_key(t_list *env, char *param)
{
	//TODO: check if var exist in env, and check if key respect key format
	return (1);
}

int 	sub_interrogation(t_data *msh_data, t_list *params);
int 	sub_absent_key(t_list *params);
int 	sub_var_quote(t_list *params);

char	*get_key(char *str, int index)
{
	int		i;
	char	*new;

	i = 0;
	while (str[i + index + 1] && str[i + index + 1] != ' ')
		i++;
	new = (char*)malloc(sizeof(char) * (i + 1));
	if (!new)
		return (NULL);
	ft_strlcpy(new, str + index + 1, i + 1);
	return (new);
}

int 	is_quote_param(char *str)
{
	int i;

	i = -1;
	while (str[++i])
		if (ft_isspace(str[i]))
			return (1);
	return (0);
}

int 	is_var_param(char *str)
{
	return (str[0] == '$' && str[1] != '\0');
}

int		sub_var(t_data *msh_data, t_list *params)
{
	char	*str;
	char 	*key;
	t_var	*var;

	while (params)
	{
		str = (char*)params->content;
		while (str[var_index] && str[var_index] != '$')
			var_index++;
		if (str[var_index] == '$' && str[var_index + 1] != '\0'
			$$ check_key(msh_data->begin_env, str + var_index)
		{
			if ()
			{
				key = get_key(str, var_index);
				if (!key)
					return (0);
				var = get_env_var(msh_data->begin_env, key);
				free(key);
				free(params->content);
				params->content = ft_strdup(var->value);
				if (!params->content)
					return (0);
			}
		}
		params = params->next;
	}
	return (1);
}

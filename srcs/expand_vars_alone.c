/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars_alone.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 18:02:11 by lsoulier          #+#    #+#             */
/*   Updated: 2021/01/15 18:02:19 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	str_has_ws(char *str)
{
	int i;

	i = -1;
	while(str[++i])
		if (ft_isspace(str[i]))
			return (1);
	return (0);
}

int expand_one_var_alone(t_data *msh_data, char ***args, int *arg_index)
{
	t_var *var;

	var = get_env_var(msh_data->begin_env, (*args)[*arg_index] + 1);
	if (!var)
		return (0);
	(*args)[*arg_index] = ft_strdup(var->value);
	if (!((*args)[*arg_index]))
		return (0);
	if (str_has_ws((*args)[*arg_index]))
	{
		if (!divide_arg(args, (*args)[*arg_index], arg_index))
			return (free_return_int((*args)[*arg_index]));
	}
	return (1);
}

int	divide_arg(char ***args, char *arg_to_divide, int *arg_index)
{
	char **arg_split;
	char **new;
	char **next_temp;

	arg_split = ft_split_charset(arg_to_divide, " \t\r\f\v\n");
	if (!arg_split)
		return (0);
	next_temp = (*args) + *arg_index + 1;
	(*args)[*arg_index] = NULL;
	new = ft_double_tab_merge(*args, arg_split);
	if (!new)
		return(free_double_tab_ret_int(arg_split));
	new = ft_double_tab_merge()
	/*char 	**first_split;
	char	**new;

	first_split = ft_split_charset((*args)[0], " \t\r\f\v\n");
	if (!first_split)
		return (0);
	new = ft_double_tab_merge(first_split, (*args + 1));
	if (!new)
		return (ft_double_tab_free(first_split) != NULL);
	ft_double_tab_free(*args);
	ft_double_tab_free(first_split);
	*args = new;*/
	return (1);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 19:28:10 by lsoulier          #+#    #+#             */
/*   Updated: 2020/12/25 20:22:33 by louise           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int 	check_key(t_list *env, char *param)
{
	//TODO: check if var exist in env, and check if key respect key format
	return (1);
}

int 	sub_interrogation(t_data *msh_data, char ***params_ptr);
int 	sub_absent_key(char ***params_ptr);

int		sub_quotes(t_list **quotes_begin, char ***params_ptr)
{
	int		i;
	char 	**params;
	char 	*quote_str;
	t_list	*el;

	i = -1;
	params = *params_ptr;
	el = *quotes_begin;
	while (params[++i])
	{
		if (ft_strnstr(params[i], "\"\"", 2)
			|| ft_strnstr(params[i], "\'\'", 2))
		{
			free(params[i]);
			quote_str = ft_strdup((char*)el->content);
			if (!quote_str)
				return (0);
			*params_ptr[i] = quote_str;
			el = el->next;
		}
	}
	ft_lstclear(quotes_begin, &free);
	return (1);
}

int 	sub_var_in_quotes(t_list *env, char **quote_str)
{
	char	**words_tab;
	char	*str_joins;
	int		nb_words;

	words_tab = ft_split(*quote_str, ' ');
	if (!words_tab)
		return (0);
	if (!sub_var(env, &words_tab))
		return (0);
	nb_words = 0;
	while (words_tab[nb_words])
		nb_words++;
	str_joins = ft_joinstrs(nb_words, words_tab, " ");
	free_double_tab(words_tab);
	if (!str_joins)
		return (0);
	free(*quote_str);
	*quote_str = str_joins;
	return (1);
}

int		sub_var(t_list *env, char ***params_ptr)
{
	int		i;
	char 	**params;
	t_var	*var;

	i = -1;
	params = *params_ptr;
	while (params[++i])
	{
		if (params[i][0] == '$' && params[i][1] != '\0')
		{
			if (!check_key(env, params[i]))
				return (0);
			var = get_env_var(env, params[i] + 1);
			free(params[i]);
			*params_ptr[i] = ft_strdup(var->value);
			if (!*params_ptr[i])
				return (0);
		}
	}
	return (1);
}

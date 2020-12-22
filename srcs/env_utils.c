/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 14:51:51 by lsoulier          #+#    #+#             */
/*   Updated: 2020/12/22 14:51:52 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list_env	*env_new_var(char *key, char *value)
{
	t_list_env *new_var;

	new_var = (t_list_env*)malloc(sizeof(t_list_env));
	if (new_var)
	{
		new_var->key = key;
		new_var->value = value;
		new_var->next = NULL;
	}
	return (new_var);
}

void	env_add_back(t_list_env **begin, t_list_env *new)
{
	t_list_env *track;

	track = *begin;
	if (track)
	{
		while (track->next)
			track = track->next;
		track->next = new;
	}
	else
		*begin = new;
}

void	env_add_front(t_list_env **begin, t_list_env *new)
{
	t_list_env *tmp;

	tmp = *begin;
	*begin = new;
	if (new)
		new->next = tmp;
}

void 	env_del_var(t_list_env **begin, t_list_env *el)
{
	t_list_env *previous;
	t_list_env *cur;

	cur = *begin;
	previous = NULL;
	if (cur)
	{
		while (cur != el)
		{
			previous = cur;
			cur = cur->next;
		}
		if (previous)
			previous->next = cur->next;
		else
			*begin = cur->next;
	}
	if (el)
	{
		free(el->key);
		free(el->value);
		free(el);
	}
}

void	env_clear(t_list_env **begin)
{
	t_list_env *track;
	t_list_env *next;

	track = *begin;
	while (track)
	{
		next = track->next;
		track->next = NULL;
		free(track->key);
		free(track->value);
		free(track);
		track = next;
	}
	*begin = NULL;
}

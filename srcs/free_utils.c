/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 21:11:19 by lsoulier          #+#    #+#             */
/*   Updated: 2021/01/10 21:11:27 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		free_return_int(void *ptr)
{
	free(ptr);
	return (0);
}

void	*free_return_null(void *ptr)
{
	free(ptr);
	return (NULL);
}

int		free_double_tab_ret_int(char **tab)
{
	int i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
	return (0);
}

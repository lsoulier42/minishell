/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 05:27:29 by lsoulier          #+#    #+#             */
/*   Updated: 2020/12/29 05:27:39 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		free_str_return_int(char *str)
{
	free(str);
	return (0);
}

void	*free_str_return_null(char *str)
{
	free(str);
	return (NULL);
}
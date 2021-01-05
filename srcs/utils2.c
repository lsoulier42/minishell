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

int	free_return_int(void *ptr)
{
	free(ptr);
	return (0);
}

void	*free_return_null(void *ptr)
{
	free(ptr);
	return (NULL);
}

int	ft_isnum(char *str)
{
	int i;

	i= -1;
	while (str[i])
		if (!ft_isdigit(str[i]))
			return (0);
	return (1);
}

int	ft_ischarset(char c, char *charset)
{
	int i;

	i = -1;
	while (charset[++i])
		if (c == charset[i])
			return (1);
	return (0);
}

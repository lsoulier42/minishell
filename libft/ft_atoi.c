/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louise <lsoulier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 22:40:54 by louise            #+#    #+#             */
/*   Updated: 2020/09/28 16:45:14 by louise           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_whitespace(int c)
{
	return (c == '\t' || c == '\n' || c == '\v'
			|| c == '\f' || c == '\r' || c == ' ');
}

int			ft_atoi(const char *str)
{
	int i;
	int nb_digit;
	int sign;
	int r_val;

	i = 0;
	sign = 1;
	r_val = 0;
	nb_digit = 0;
	while (is_whitespace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		sign = str[i] == '-' ? -1 : 1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		r_val = r_val * 10 + str[i] - '0';
		i++;
		nb_digit++;
	}
	if (nb_digit >= 19)
		return (sign == 1 ? -1 : 0);
	return (r_val * sign);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louise <lsoulier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 18:32:26 by louise            #+#    #+#             */
/*   Updated: 2020/09/24 15:17:31 by louise           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_char(int n)
{
	int		nb_char;
	long	nb;

	nb_char = n < 0 ? 2 : 1;
	nb = n < 0 ? -(long)n : n;
	while (nb / 10 != 0)
	{
		nb_char++;
		nb /= 10;
	}
	return (nb_char);
}

char		*ft_itoa(int n)
{
	char	*str;
	int		nb_char;
	long	abs_n;

	nb_char = count_char(n);
	abs_n = n < 0 ? -(long)n : n;
	if (!(str = (char*)malloc(sizeof(char) * (nb_char + 1))))
		return (NULL);
	str[nb_char] = '\0';
	while (--nb_char > 0)
	{
		str[nb_char] = abs_n % 10 + '0';
		abs_n /= 10;
	}
	str[0] = n < 0 ? '-' : abs_n % 10 + '0';
	return (str);
}

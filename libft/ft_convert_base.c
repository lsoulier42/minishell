/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louise <lsoulier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 14:48:44 by louise            #+#    #+#             */
/*   Updated: 2020/09/28 15:01:22 by louise           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_nbr_len(long nbr, int base_len)
{
	int nbr_len;

	nbr_len = nbr < base_len ? 1 : 2;
	while (nbr / base_len >= base_len)
	{
		nbr /= base_len;
		nbr_len++;
	}
	return (nbr_len);
}

static char	*converted_nbr(int int_nbr, char *base_to)
{
	char	*r_nbr_base;
	int		nbr_len;
	int		nbr;
	int		base_to_len;

	base_to_len = ft_strlen(base_to);
	nbr = int_nbr < 0 ? -int_nbr : int_nbr;
	nbr_len = int_nbr < 0 ? 1 : 0;
	nbr_len += count_nbr_len(nbr, base_to_len);
	if (!(r_nbr_base = malloc((nbr_len + 1) * sizeof(char))))
		return (NULL);
	r_nbr_base[nbr_len] = '\0';
	while (nbr_len-- > 0)
	{
		r_nbr_base[nbr_len] = base_to[nbr % base_to_len];
		nbr /= base_to_len;
	}
	r_nbr_base[0] = int_nbr < 0 ? '-' : r_nbr_base[0];
	return (r_nbr_base);
}

char		*ft_convert_base(char *nbr, char *base_from, char *base_to)
{
	int		int_nbr;

	if (ft_check_base(base_from) && ft_check_base(base_to))
	{
		int_nbr = ft_atoi_base(nbr, base_from);
		return (converted_nbr(int_nbr, base_to));
	}
	return (NULL);
}

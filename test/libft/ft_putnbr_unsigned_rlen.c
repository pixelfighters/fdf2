/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_unsigned_rlen.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuh <fschuh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:13:38 by marvin            #+#    #+#             */
/*   Updated: 2024/06/04 17:22:54 by fschuh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_unsigned_rlen(unsigned int n, int rlen)
{
	unsigned int	nbr;

	nbr = n;
	if (nbr > 9)
	{
		rlen = ft_putnbr_unsigned_rlen(nbr / 10, rlen + 1);
	}
	else
		rlen++;
	ft_putchar(nbr % 10 + '0');
	return (rlen);
}

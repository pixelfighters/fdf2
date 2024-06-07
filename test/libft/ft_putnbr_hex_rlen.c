/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hex_rlen.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuh <fschuh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:13:38 by marvin            #+#    #+#             */
/*   Updated: 2024/06/04 17:09:10 by fschuh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	ft_check_case(int i, char uppercase)
{
	if (uppercase == 'X')
		return ('A' + (i - 10));
	else if (uppercase == 'x')
		return ('a' + (i - 10));
	else
		return (0);
}

int	ft_putnbr_hex_rlen(unsigned int n, int rlen, char uppercase)
{
	char	hex_digits[16];
	int		i;

	i = 0;
	while (i < 10)
	{
		hex_digits[i] = '0' + i;
		i++;
	}
	while (i < 16)
	{
		hex_digits[i] = ft_check_case(i, uppercase);
		i++;
	}
	if (n >= 16)
		rlen = ft_putnbr_hex_rlen(n / 16, rlen + 1, uppercase);
	else
		rlen++;
	ft_putchar(hex_digits[n % 16]);
	return (rlen);
}

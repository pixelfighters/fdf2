/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr_rlen.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuh <fschuh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:40:55 by marvin            #+#    #+#             */
/*   Updated: 2024/05/24 09:52:45 by fschuh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_hexptr_rlen(uintptr_t num, char *hex_digits, int *rlen)
{
	if (num >= 16)
	{
		ft_putnbr_hexptr_rlen(num / 16, hex_digits, rlen);
	}
	ft_putchar(hex_digits[num % 16]);
	return ((*rlen)++);
}

int	ft_putptr_rlen(void *ptr)
{
	int			rlen;
	uintptr_t	addr;
	char		hex_digits[16];
	const char	*temp = "0123456789abcdef";
	int			i;

	addr = (uintptr_t)ptr;
	i = 0;
	while (i < 16)
	{
		hex_digits[i] = temp[i];
		i++;
	}
	rlen = 1;
	if (addr == 0)
	{
		ft_putstr("(nil)");
		rlen += 4;
	}
	else
	{
		ft_putstr("0x");
		rlen = (ft_putnbr_hexptr_rlen(addr, hex_digits, &rlen) + 2);
	}
	return (rlen);
}

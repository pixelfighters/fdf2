/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_binary.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuh <fschuh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:40:01 by fschuh            #+#    #+#             */
/*   Updated: 2024/06/04 16:01:05 by fschuh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h" 

void	ft_print_binary(unsigned int num)
{
	unsigned int	mask;
	int				i;

	mask = 0x80000000;
	i = -1;
	printf("0b");
	while (++i < 32)
	{
		if (num & mask)
		{
			printf("1");
		}
		else
		{
			printf("0");
		}
		num <<= 1;
		if (i % 8 == 7 && i != 31)
			printf(" ");
	}
	printf("\n");
}

int	ft_create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	main(void)
{
	unsigned int number;

	number = ft_create_trgb(255, 255, 255, 255);
	ft_print_binary(number);
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuh <fschuh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:49:33 by fschuh            #+#    #+#             */
/*   Updated: 2024/04/26 11:38:18 by fschuh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

static	int	ft_intlen(int n)
{
	if (!n)
		return (0);
	return (1 + ft_intlen(n / 10));
}

static	void	ft_intwrite(int n, char *write, int len)
{
	int	value;
	int	i;

	if (!len)
		*write = '\0';
	else
	{
		value = n;
		i = 1;
		while (i++ < len)
			value /= 10;
		if (n < 0)
			*write = '0' - value % 10;
		else
			*write = '0' + value % 10;
		ft_intwrite(n, write + 1, len - 1);
	}
}

char	*ft_itoa(int n)
{
	int		len;
	char	*out;

	if (!n)
		len = 1;
	else if (n > 0)
		len = ft_intlen(n);
	else
		len = ft_intlen(n) + 1;
	out = (char *)malloc((len + 1) * sizeof(char));
	if (!out)
		return (0);
	if (n < 0)
	{
		*out = '-';
		ft_intwrite(n, out + 1, len - 1);
	}
	else
		ft_intwrite(n, out, len);
	return (out);
}

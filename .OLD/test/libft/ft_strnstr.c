/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuh <fschuh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:47:57 by fschuh            #+#    #+#             */
/*   Updated: 2024/04/23 15:03:17 by fschuh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *c, size_t num)
{
	size_t	i;
	size_t	j;	

	i = 0;
	j = 0;
	if (c[0] == 0)
		return ((char *) str);
	while (str[i] && i < num)
	{
		while (str[i + j] == c[j] && str[i + j] && i + j < num)
		{
			j++;
			if (c[j] == 0)
				return ((char *) str + i);
		}
		i++;
		j = 0;
	}
	return (0);
}

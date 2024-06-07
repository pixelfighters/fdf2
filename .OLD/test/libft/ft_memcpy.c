/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuh <fschuh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:25:39 by fschuh            #+#    #+#             */
/*   Updated: 2024/04/26 10:23:36 by fschuh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*tmp_dest;
	unsigned char	*tmp_src;

	tmp_dest = (unsigned char *) dest;
	tmp_src = (unsigned char *) src;
	if (!n || dest == src)
		return (dest);
	if (!dest && !src)
		return (NULL);
	while (n--)
	{
		*(tmp_dest++) = *(tmp_src++);
	}
	return (dest);
}

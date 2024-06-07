/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuh <fschuh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:04:37 by fschuh            #+#    #+#             */
/*   Updated: 2024/04/25 18:49:56 by fschuh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	void	*tmp;

	if ((int)num < 0 && (int)size < 0)
	{
		return (NULL);
	}
	tmp = (void *)malloc(num * size);
	if (!tmp)
		return (NULL);
	ft_bzero(tmp, num * size);
	return ((void *)tmp);
}

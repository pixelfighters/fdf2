/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuh <fschuh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:32:24 by fschuh            #+#    #+#             */
/*   Updated: 2024/04/25 18:44:04 by fschuh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int character)
{
	char	char_to_find;
	int		i;

	char_to_find = (char)character;
	if (character == '\0')
	{
		while (*str)
			str++;
		return ((char *)str);
	}
	i = ft_strlen(str);
	while (i >= 0)
	{
		if (str[i] == char_to_find)
		{
			return ((char *) &str[i]);
		}
		i--;
	}
	return (NULL);
}

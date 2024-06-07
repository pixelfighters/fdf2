/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuh <fschuh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:35:41 by fschuh            #+#    #+#             */
/*   Updated: 2024/04/29 13:35:43 by fschuh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str1)
{
	size_t	strlen;
	size_t	i;
	char	*returnstr;

	i = 0;
	strlen = ft_strlen(str1);
	returnstr = malloc((strlen + 1) * sizeof(char));
	if (!returnstr)
		return (NULL);
	while (str1[i])
	{
		returnstr[i] = str1[i];
		i++;
	}
	returnstr[i] = '\0';
	return (returnstr);
}

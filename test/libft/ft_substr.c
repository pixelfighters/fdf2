/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuh <fschuh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 08:52:02 by fschuh            #+#    #+#             */
/*   Updated: 2024/04/26 12:29:35 by fschuh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*returnstring;	

	i = 0;
	if (start > (unsigned int)ft_strlen(s))
	{
		return (ft_strdup(""));
	}
	if (len > (unsigned int)ft_strlen(s + start))
		len = (unsigned int)ft_strlen(s + start);
	returnstring = ft_calloc(len + 1, sizeof(char));
	if (!returnstring)
		return (NULL);
	i = 0;
	while (i < len)
	{
		returnstring[i] = s[start + i];
		i++;
	}
	return (returnstring);
}

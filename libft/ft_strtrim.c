/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuh <fschuh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 08:52:02 by fschuh            #+#    #+#             */
/*   Updated: 2024/04/26 11:57:37 by fschuh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	trimmable(char stringpos, const char *set);

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	i;
	size_t	j;
	char	*returnstring;
	char	*returnstringstart;

	i = 0;
	j = ft_strlen(s1) - 1;
	if (ft_strlen(s1) == 0)
		return (ft_strdup(""));
	while ((trimmable(s1[i], set)))
		i++;
	while ((trimmable(s1[j], set)) && i < j)
		j--;
	returnstring = (char *)malloc(sizeof(char) * (j - i + 2));
	if (!returnstring)
		return (NULL);
	returnstringstart = returnstring;
	while (s1[i] && i <= j)
	{
		*returnstring = s1[i];
		returnstring++;
		i++;
	}
	*returnstring = '\0';
	return (returnstringstart);
}

static int	trimmable(char stringpos, const char *set)
{
	while (*set && stringpos != '\0')
	{
		if (stringpos == *set)
			return (1);
		set++;
	}
	return (0);
}

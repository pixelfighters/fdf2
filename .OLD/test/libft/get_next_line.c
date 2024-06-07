/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuh <fschuh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 10:19:59 by kami              #+#    #+#             */
/*   Updated: 2024/06/04 17:14:35 by fschuh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_find_n(char *str, size_t i)
{
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	return (i);
}

char	*ft_get_string(char *str)
{
	char	*new_str;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (str[i] == '\0')
		return (free(str), NULL);
	i = ft_find_n(str, i);
	new_str = (char *)malloc((ft_strlen(str) - i + 1));
	if (!new_str)
		return (free(new_str), NULL);
	while (str[i])
		new_str[j++] = str[i++];
	new_str[j] = '\0';
	if (!new_str[0])
		return (free(str), free(new_str), NULL);
	free(str);
	return (new_str);
}

char	*ft_read_the_line(char *str)
{
	char	*line;
	size_t	i;

	i = 0;
	if (!str || str[0] == '\0')
		return (NULL);
	i = ft_find_n(str, i);
	line = (char *)malloc(sizeof(char) * i + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		line[i] = str[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_free(char *buff1, char **buff2)
{
	free(buff1);
	if (buff2)
	{
		free(*buff2);
		*buff2 = NULL;
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*r_buffer[MAX_FD];
	char		*r_content;
	ssize_t		r_bytes;

	r_bytes = 1;
	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	r_content = (char *)malloc((sizeof(char) * BUFFER_SIZE) + 1);
	if (!r_content)
		return (NULL);
	while (!ft_strchr(r_buffer[fd], '\n') && r_bytes > 0)
	{
		r_bytes = read(fd, r_content, BUFFER_SIZE);
		if (r_bytes == -1)
			return (ft_free(r_content, &r_buffer[fd]));
		r_content[r_bytes] = '\0';
		if (ft_is_binary(r_content, r_bytes))
			return (ft_free(r_content, &r_buffer[fd]));
		r_buffer[fd] = ft_strjoin(r_buffer[fd], r_content);
	}
	free(r_content);
	r_content = ft_read_the_line(r_buffer[fd]);
	r_buffer[fd] = ft_get_string(r_buffer[fd]);
	return (r_content);
}

int main() 
{
	// int fd = open("a.out", O_RDONLY);
	int fd = open("test.txt", O_RDONLY);
	if (fd == -1) {
		printf("Error opening file\n");
		return 1;
	}
	char *line;
	while ((line = get_next_line(fd)) != NULL) {
		printf("%s\n", line);
		free(line);
	}
	close(fd);
	return 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoropeza <aoropeza@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 16:58:53 by aoropeza          #+#    #+#             */
/*   Updated: 2022/06/28 14:36:27 by aoropeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"
#include <stdio.h>

static char	*join(char *buf, char *buffer)
{
	char	*temp;

	temp = ft_strjoin(buffer, buf);
	free(buffer);
	buffer = temp;
	return (buffer);
}

static char	*read_file(int fd, char *buffer)
{
	char		*buf;
	int			reader;

	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	reader = 1;
	while (reader > 0 && !ft_strchr(buffer, '\n'))
	{
		reader = read(fd, buf, BUFFER_SIZE);
		if (reader == -1)
		{
			free (buf);
			return (NULL);
		}
		buf[reader] = '\0';
		buffer = join(buf, buffer);
		if (buffer[0] == 0)
		{
			free (buf);
			free (buffer);
			return (NULL);
		}
	}
	free (buf);
	return (buffer);
}

static char	*get_line(char *buffer)
{
	char	*line;
	size_t	size;

	size = 0;
	while (buffer[size] && buffer[size] != '\n')
		size++;
	line = ft_substr(buffer, 0, size + 1);
	return (line);
}

static char	*get_end(char *buffer)
{
	char	*new_line;
	size_t	index;
	size_t	len;

	index = 0;
	len = 0;
	while (buffer[index] && buffer[index] != '\n')
		index++;
	if (!buffer[index])
	{
		free (buffer);
		return (NULL);
	}
	index++;
	while (buffer[index + len] && buffer[index + len] != '\0')
		len++;
	new_line = ft_substr(buffer, index, len);
	free (buffer);
	return (new_line);
}

char	*get_next_line(int fd)
{
	static char	*buffer[4096];
	char		*line;

	if (fd < 0 || fd > 4096 || read(fd, 0, 0) || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer[fd])
		buffer[fd] = ft_strdup("");
	buffer[fd] = read_file(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	line = get_line(buffer[fd]);
	buffer[fd] = get_end(buffer[fd]);
	return (line);
}

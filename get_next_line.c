/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarikha <asarikha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:23:27 by asarikha          #+#    #+#             */
/*   Updated: 2023/01/23 14:43:32 by asarikha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*join_and_free_buffer(char *buffer, char *buf)
{
	char	*temp;

	temp = ft_strjoin(buffer, buf);
	free(buffer);
	return (temp);
}

static char	*get_next(char *buffer)
{
	int		i;
	int		j;
	char	*next_line;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	next_line = ft_calloc((ft_strlen(buffer) - i + 1), sizeof(char));
	i++;
	j = 0;
	while (buffer[i])
		next_line[j++] = buffer[i++];
	free(buffer);
	return (next_line);
}

static char	*get_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] && buffer[i] == '\n')
		line[i++] = '\n';
	return (line);
}

static char	*read_line(int fd, char *buffer)
{
	char	buf[BUFFER_SIZE + 1];
	int		byte_read;
	int		nl_found;

	nl_found = 0;
	if (!buffer)
		buffer = ft_calloc(1, 1);
	byte_read = 1;
	while (byte_read > 0 && !nl_found)
	{
		byte_read = read(fd, buf, BUFFER_SIZE);
		if (byte_read == -1)
			return (NULL);
		buf[byte_read] = 0;
		buffer = join_and_free_buffer(buffer, buf);
		if (ft_strchr(buf, '\n'))
			nl_found = 1;
	}
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buffer = read_line(fd, buffer);
	if (!buffer)
		return (NULL);
	line = get_line(buffer);
	if (!line)
		return (NULL);
	buffer = get_next(buffer);
	// if (!buffer)
	// 	return (NULL);
	return (line);
}

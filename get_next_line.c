/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfamilar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 12:48:06 by cfamilar          #+#    #+#             */
/*   Updated: 2022/09/01 20:32:53 by cfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*trim_line_and_get_leftover(char *line)
{
	int		i;
	char	*leftover;

	i = 0;
	leftover = NULL;
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	if (line[i] == '\0')
		return (leftover);
	if (line[i + 1] != '\0')
		leftover = ft_substr(line, i + 1, ft_strlen(line) - i);
	line[i + 1] = '\0';
	return (leftover);
}

char	*find_new_line(int fd, char *buffer, char *unread_string)
{
	int		bytes_read;
	char	*temp;

	bytes_read = 1;
	while (bytes_read)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (NULL);
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		if (!unread_string)
			unread_string = ft_strdup("");
		temp = unread_string;
		unread_string = ft_strjoin(temp, buffer);
		free(temp);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (unread_string);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*line;
	static char	*unread_string[1024];

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= 1024 || read(fd, 0, 0) < 0)
		return (NULL);
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	line = find_new_line(fd, buffer, unread_string[fd]);
	free(buffer);
	buffer = NULL;
	if (!line)
		return (line);
	unread_string[fd] = trim_line_and_get_leftover(line);
	return (line);
}

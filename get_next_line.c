/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfamilar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 12:48:06 by cfamilar          #+#    #+#             */
/*   Updated: 2022/09/09 18:45:23 by cfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(const char *s)
{
	int	i;

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
	if (line[i] == '\0' || line[1] == '\0')
		return (NULL);
	leftover = ft_substr(line, i + 1, ft_strlen(line) - (i + 1));
	if (*leftover == '\0')
	{
		free(leftover);
		leftover = NULL;
	}
	line[i + 1] = '\0';
	return (leftover);
}

char	*find_new_line(int fd, char *unread_string)
{
	int		bytes_read;
	char	*buffer;

	buffer = (char *) malloc ((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (0);
	bytes_read = 1;
	while (!ft_strchr(unread_string, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free (buffer);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		unread_string = ft_strjoin(unread_string, buffer);
	}
	free (buffer);
	return (unread_string);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*unread_string[FOPEN_MAX];

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > FOPEN_MAX || read(fd, 0, 0) < 0)
		return (NULL);
	unread_string[fd] = find_new_line(fd, unread_string[fd]);
	if (!line)
		return (line);
	line
	unread_string[fd] = trim_line_and_get_leftover(line);
	return (line);
}

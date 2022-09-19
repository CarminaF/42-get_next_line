/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfamilar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 12:48:06 by cfamilar          #+#    #+#             */
/*   Updated: 2022/09/10 11:24:12 by cfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*trim_line_and_get_leftover(char *line)
{
	int		i;
	int		j;
	char	*leftover;

	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	if (!line[i])
	{
		free (line);
		return (0);
	}
	leftover = (char *) malloc (sizeof(char) * (ft_strlen(line) - i + 1));
	if (!leftover)
		return (0);
	j = 0;
	i++;
	while (line[i])
		leftover[j++] = line[i++];
	leftover[j] = '\0';
	free (line);
	return (leftover);
}

char	*find_new_line(char *str)
{
	int		i;
	char	*line;

	i = 0;
	if (!str[i])
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (0);
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

char	*buffer_read(int fd, char *str)
{
	char	*buffer;
	int		bytes_read;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (0);
	bytes_read = 1;
	while (!ft_strchr(str, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free (buffer);
			return (0);
		}
		buffer[bytes_read] = '\0';
		str = ft_strjoin(str, buffer);
	}
	free (buffer);
	return (str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*unread_string[FOPEN_MAX];

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > FOPEN_MAX || read(fd, 0, 0) < 0)
		return (NULL);
	unread_string[fd] = buffer_read(fd, unread_string[fd]);
	if (!unread_string[fd])
		return (0);
	line = find_new_line(unread_string[fd]);
	unread_string[fd] = trim_line_and_get_leftover(unread_string[fd]);
	return (line);
}
/*
int	main(void)
{
	char	*line1;
	int	fd1;

	fd1 = open("test1.txt", O_RDONLY);

	while (1)
	{
		line1 = get_next_line(fd1);
		if (line1)
			printf("gnl return: %s", line1);
		else
			break ;
		free(line1);
	}
	close(fd1);
	return (0);
}*/

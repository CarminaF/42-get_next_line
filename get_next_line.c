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

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*trim_line_and_get_leftover(char *line)
{
	int		i;
	char	*leftover;

	i = 0;
	leftover = NULL;
	if (!line[i])
		return (NULL);
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	if (line[i] == '\0')
		return (leftover);
	if (line[i + 1] != '\0')
		leftover = ft_substr(line, i + 1, ft_strlen(line) - (i + 1));
	line[i + 1] = '\0';
	return (leftover);
}

char	*find_new_line(int fd, char *buffer, char *unread_string)
{
	int		bytes_read;
	char	*temp;

	bytes_read = 1;
	while (bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (NULL);
		else if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		if (!unread_string)
			unread_string = ft_strdup("");
		temp = unread_string;
		unread_string = ft_strjoin(temp, buffer);
		free(temp);
		temp = NULL;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (unread_string);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*line;
	static char	*unread_string[FOPEN_MAX];

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > FOPEN_MAX || read(fd, 0, 0) < 0)
		return (NULL);
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	line = find_new_line(fd, buffer, unread_string[fd]);
	free(buffer);
	buffer = NULL;
	if (!line)
		return (NULL);
	unread_string[fd] = trim_line_and_get_leftover(line);
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

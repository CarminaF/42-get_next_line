/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfamilar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 12:48:06 by cfamilar          #+#    #+#             */
/*   Updated: 2022/09/13 17:12:28 by cfamilar         ###   ########.fr       */
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

char	*get_trimmed_line(char *str, int new_line_pos)
{
	int		i;
	char	*trimmed;
	
	if (new_line_pos == 0)
		new_line_pos = ft_strlen(str);
	//printf("new_line_pos is: %i\n", new_line_pos);
	trimmed = (char *) malloc (sizeof(char) * (new_line_pos + 1));
	i = 0;
	trimmed[i] = '\0';
	while (i < new_line_pos)
	{
		trimmed[i] = str[i];
		i++;
	}
	free (str);
	str = NULL;
	return (trimmed);
}

char	*find_new_line_with_leftover(int fd, char *buffer, char *str)
{
	int		bytes_read;
	char	*temp;
	int		i;

	bytes_read = 1;
	i = 0;
	while (!new_line_position(str))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		//printf("bytes_read: %i\nwhile loop iteration:%i\n", bytes_read, ++i);
		if (bytes_read == -1)
			return (NULL);
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		if (!str)
			str = ft_strdup("");
		temp = str;
		str = ft_strjoin(temp, buffer);
		free(temp);
		temp = NULL;
	}
	return (str);
}

char	*get_leftover(char *str, int pos)
{
	char	*leftover;
	int		leftover_len;
	int		i;
	int		j;
	
	leftover = NULL;
	leftover_len = ft_strlen(str) - pos;
	if (leftover_len != ft_strlen(str) && leftover_len > 0)
	{
		leftover = (char *)malloc(sizeof(char) * (leftover_len + 1));
		i = 0;
		j = pos;
		while (j <= leftover_len)
		{
			//printf("j is : %i\n", j);
			leftover[i++] = str[j++];
		}
		leftover[i] = '\0';
	}
	return (leftover);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*line;
	static char	*unread_string[FOPEN_MAX];

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > FOPEN_MAX || read(fd, 0, 0) < 0)
		return (NULL);
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	unread_string[fd] = find_new_line_with_leftover(fd, buffer, unread_string[fd]);
	//printf("unread_string[fd]: %s\n", unread_string[fd]);
	free(buffer);
	buffer = NULL;
	if (!unread_string[fd])
		return (NULL);
	line = get_trimmed_line(unread_string[fd], new_line_position(unread_string[fd]));
	unread_string[fd] = get_leftover(line, new_line_position(line));
	return (line);
}
/*
int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (line)
			printf("gnl return: %s", line);
		else 
			break ;
		free (line);
	}
	close (fd);
}*/
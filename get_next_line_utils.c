/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfamilar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 12:48:34 by cfamilar          #+#    #+#             */
/*   Updated: 2022/09/07 18:14:13 by cfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(char *s, int c)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(s);
	while (i <= len)
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	return (NULL);
}

int	get_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

char	*ft_substr(char *s, int start, int len)
{
	char	*p;
	int		i;
	int		j;

	if (start >= ft_strlen(s))
	{
		p = malloc(sizeof(char));
		if (!p)
			return (NULL);
		else
			p[0] = '\0';
		return (p);
	}
	len = get_min(len, ft_strlen(s) - start);
	p = malloc(sizeof(char) * len + 1);
	if (!p || !s)
		return (NULL);
	i = start;
	j = 0;
	while (i < ft_strlen(s) && j < len)
		p[j++] = s[i++];
	p[j] = '\0';
	return (p);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*res;
	int		i;
	int		j;

	res = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!res || !s1 || !s2)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		res[i + j] = s2[j];
		j++;
	}
	res[i + j] = '\0';
	return (res);
}

char	*ft_strdup(char *s1)
{
	int		i;
	char	*res;

	i = 0;
	res = (char *) malloc ((ft_strlen(s1) + 1) * sizeof (char));
	if (!res)
		return (NULL);
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

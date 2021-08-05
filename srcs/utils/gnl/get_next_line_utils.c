/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <rmeiboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/25 15:38:30 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/05/15 12:17:06 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (str)
	{
		while (str[i])
			i++;
	}
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	char		*str;
	char		*cursor;
	size_t		i;
	size_t		len;

	if (!s)
		return (NULL);
	str = (char *)s;
	len = ft_strlen(str);
	i = 0;
	if (c == '\0' && str[len] == c)
	{
		cursor = &str[len];
		return (cursor);
	}
	while (str[i])
	{
		if (str[i] == c)
		{
			cursor = &str[i];
			return (cursor);
		}
		i++;
	}
	return (NULL);
}

char	*ft_strdup(const char *s1)
{
	char		*str;
	char		*ptr;
	size_t		i;

	i = 0;
	str = (char *)s1;
	ptr = (char *)ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!ptr)
		return (NULL);
	while (str[i])
	{
		ptr[i] = str[i];
		i++;
	}
	return (ptr);
}

char	*ft_gnl_strjoin(char *s1, char *s2)
{
	size_t	len1;
	size_t	i;
	char	*joined;

	len1 = ft_strlen((char *)s1);
	i = 0;
	joined = ft_calloc(sizeof(char), (len1 + ft_strlen(s2) + 1));
	if (!joined)
		return (NULL);
	while (s1 != NULL && (s1[i] && s1[i] != '\n'))
	{
		joined[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2 != NULL && (s2[i] != '\n' && s2[i]))
	{
		joined[i + len1] = s2[i];
		i++;
	}
	if (s1)
		free(s1);
	return (joined);
}

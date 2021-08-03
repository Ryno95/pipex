/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/29 17:34:18 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/05/15 12:18:19 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	ft_bzero(void *str, size_t n)
{
	size_t	i;
	char	*string;

	i = 0;
	string = (char *)str;
	while (i < n)
	{
		string[i] = '\0';
		i++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*voidptr;
	size_t	true_size;
	size_t	i;

	i = 0;
	true_size = count * size;
	voidptr = malloc(true_size);
	if (!voidptr)
		return (NULL);
	else
	{
		while (i < true_size)
		{
			((char *)voidptr)[i] = '\0';
			i++;
		}
	}
	return (voidptr);
}

static int	check_leftovers(char **leftovers, char **line, char **strt)
{
	if (!*leftovers || !*strt)
		return (0);
	if (ft_strchr(*leftovers, '\n'))
	{
		*line = ft_gnl_strjoin(*line, *leftovers);
		if (!*line)
			return (-1);
		*leftovers += ft_strlen(*line) + 1;
		return (1);
	}
	else if (!ft_strchr(*leftovers, '\n') && ft_strlen(*leftovers) > 0)
	{
		*line = ft_strdup(*leftovers);
		if (!*line)
			return (-1);
		*leftovers = NULL;
	}
	if (*leftovers == NULL || (*leftovers[0] == '\0' && *strt))
	{
		free(*strt);
		*leftovers = NULL;
	}
	return (0);
}

static int	read_until_nl(int fd, char **line, char **leftovers, char **start)
{
	int		read_bytes;
	char	buffer[BUFFER_SIZE + 1];

	read_bytes = 1;
	ft_bzero(buffer, BUFFER_SIZE + 1);
	while (!ft_strchr(buffer, '\n') && read_bytes > 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
			return (read_bytes);
		else if (read_bytes == 0 && ft_strlen(*line) > 0)
			return (0);
		buffer[read_bytes] = '\0';
		*line = ft_gnl_strjoin(*line, buffer);
		if (!line)
			return (-1);
	}
	if (read_bytes > 0)
	{
		*start = ft_strdup(ft_strchr(buffer, '\n') + 1);
		if (!*start)
			return (-1);
		*leftovers = *start;
	}
	return (read_bytes);
}

int	get_next_line(int fd, char **line)
{
	int			read_result;
	static char	*leftovers;
	static char	*start;
	int			fake_bool;
	char		*ret_str;

	if (fd < 0 || BUFFER_SIZE <= 0 || !line)
		return (-1);
	ret_str = NULL;
	fake_bool = check_leftovers(&leftovers, &ret_str, &start);
	if (fake_bool == 1)
	{
		*line = ret_str;
		return (1);
	}
	else if (fake_bool == -1)
		return (-1);
	read_result = read_until_nl(fd, &ret_str, &leftovers, &start);
	*line = ret_str;
	if (read_result > 0)
		return (1);
	return (read_result);
}

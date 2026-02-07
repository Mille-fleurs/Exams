/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   broken_gnl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 10:30:29 by chitoupa          #+#    #+#             */
/*   Updated: 2026/02/07 23:04:49 by chitoupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "broken_gnl.h"

char	*ft_strchr(char *s, int c)
{
	int	i;

	if (!s)
		return (NULL);
	i = 0;
    while (s[i])
    {
        if (s[i] == (char)c)
            return (char *)(s + i);
        i++;
    }
	if ((char)c == '\0')
		return ((char *)(s + i));
    return (NULL);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
    size_t i;

    i = 0;
    while (i < n)
    {
        ((char *)dest)[i] = ((char *)src)[i];
        i++;
    }
    return (dest);
}
 
size_t  ft_strlen(char *s)
{
    size_t len;

	if (!s)
		return (0);
    len = 0;
    while(s[len])
        len++;
    return (len);
}

int	str_append_mem(char **s1, char *s2, size_t size2)
{
    size_t	size1;
	char	*newbuff;

	size1 = ft_strlen(*s1);
	newbuff = malloc(size1 + size2 + 1);
	if (!newbuff)
		return (0);
	if (size1 > 0)
		ft_memcpy(newbuff, *s1, size1);
	if (size2 > 0)
		ft_memcpy(newbuff + size1, s2, size2);
	newbuff[size1 + size2] = '\0';
	free(*s1);
	*s1 = newbuff;
	return (1);
}

int str_append_str(char **s1, char *s2)
{
    size_t size2 = ft_strlen(s2);
	return str_append_mem(s1, s2, size2);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;
	unsigned char *d;
	const unsigned char	*s;

	if (!dest && !src)
		return (NULL);
	if (dest == src || n == 0)
		return (dest);
	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	if (d < s)
	{
		i = 0;
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
	}
	else
	{
		while (n > 0)
		{
			n--;
			d[n] = s[n];
		}
	}
	return (dest);
}

char *get_next_line(int fd)
{
	static char b[BUFFER_SIZE + 1];
	char *line = NULL;
	char *nl = ft_strchr(b, '\n');

	while (!nl)
	{
		if (!str_append_str(&line, b))
			return (free(line), NULL);
		int read_ret = read(fd, b, BUFFER_SIZE);
		if (read_ret == -1)
			return (free(line), NULL);
		b[read_ret] = '\0';
		if (read_ret == 0)
		{
			if (line && *line)
				return (line);
			free(line);
			return (NULL);
		}
		nl = ft_strchr(b, '\n');
	}
	if (!str_append_mem(&line, b, nl - b + 1))
		return (free(line), NULL);
	ft_memcpy(b, nl + 1, ft_strlen(nl + 1) + 1);
	return (line);
}
/*
#include <fcntl.h>
#include <stdio.h>

static void	read_from_fd(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
}

int	main(int ac, char **av)
{
	int	fd;
	int	i;

	if (ac == 1)
	{
		read_from_fd(0);
		return (0);
	}
	i = 1;
	while (i < ac)
	{
		fd = open(av[i], O_RDONLY);
		if (fd < 0)
		{
			printf("failed to open the file %s\n", av[i]);
			i++;
			continue ;
		}
		printf("\n-------- %s --------\n", av[i]);
		read_from_fd(fd);
		close(fd);
		i++;
	}
	return (0);
}*/
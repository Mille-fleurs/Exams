/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   broken_gnl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 10:30:29 by chitoupa          #+#    #+#             */
/*   Updated: 2026/02/04 18:27:41 by chitoupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "broken_gnl.h"

static char	*ft_strchr(char *s, int c)
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

static void	*ft_memcpy(void *dest, const void *src, size_t n)
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

static size_t  ft_strlen(char *s)
{
    size_t line;

	if (!s)
		return (0);
    line = 0;
    while(s[line])
        line++;
    return (line);
}

static int	append_mem(char **s1, char *s2, size_t size2)
{
    size_t	size1;
	char	*oldbuff;

	size1 = ft_strlen(*s1);
	oldbuff = malloc(size1 + size2 + 1);
	if (!oldbuff)
		return (0);
	if (size1 > 0)
		ft_memcpy(oldbuff, *s1, size1);
	if (size2 > 0)
		ft_memcpy(oldbuff + size1, s2, size2);
	oldbuff[size1 + size2] = '\0';
	free(*s1);
	*s1 = oldbuff;
	return (1);
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

char	*get_next_line(int fd)
{
	char	*line;
	char	*nl;
	ssize_t 	read_ret;
	static char b[BUFFER_SIZE + 1];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	while (1)
	{
		nl = ft_strchr(b, '\n');
		if (nl)
		{
			if (!append_mem(&line, b, (size_t)(nl - b + 1)))
				return (free(line), NULL);
			ft_memmove(b, nl + 1, ft_strlen(nl +1) + 1);
			return (line);
		}
		if (b[0] != '\0')
		{
			if (!append_mem(&line, b, ft_strlen(b)))
				return (free(line), NULL);
			b[0] = '\0';
		}
		read_ret = read(fd, b, BUFFER_SIZE);
		if (read_ret < 0)
			return (free(line), NULL);
		if (read_ret == 0)
		{
			b[0] = '\0';
			if (line && *line)
				return (line);
			free(line);
			return (NULL);
		}
		b[read_ret] = '\0';
	}
}

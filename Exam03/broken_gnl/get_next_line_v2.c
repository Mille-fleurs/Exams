/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_v2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 18:04:17 by chitoupa          #+#    #+#             */
/*   Updated: 2026/02/10 09:14:31 by chitoupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char    *ft_strchr(char *s, int c)
{
    while (*s)
    {
        if (*s == (char)c)
            return (char *)s;
        s++;
    }
    return (NULL);
}

void    *ft_memcpy(void *dest, const void *src, size_t n)
{
    size_t i = 0;

    while (i < n)
    {
        ((char *)dest)[i] = ((char *)src)[i];
        i++;
    }
    return (dest);
}

size_t  ft_strlen(char *s)
{
    size_t res = 0;

    if (!s)
        return (0);
    while (s[res])
        res++;
    return (res);
}

int     str_append_mem(char **s1, char *s2, size_t size2)
{
    size_t size1 = ft_strlen(*s1);
    char    *tmp = malloc(size1 + size2 + 1);

    if (!tmp)
        return (0);
    if (size1 > 0)
        ft_memcpy(tmp, *s1, size1);
    if (size2 > 0)
        ft_memcpy(tmp + size1, s2, size2);
    tmp[size1 + size2] = '\0';
    free(*s1);
    *s1 = tmp;
    return (1);
}

int str_append_str(char **s1, char *s2)
{
    return (str_append_mem(s1, s2, ft_strlen(s2)));
}

char    *get_next_line(int fd)
{
    char b[BUFFER_SIZE + 1];
    char    *line = NULL;
    char    *nl = ft_strchr(b, '\n');

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

#include <fcntl.h>

void    read_from_fd(int fd)
{
    char    *line;

    line = get_next_line(fd);
    while(line)
    {
        printf("%s", line);
        free(line);
        line = get_next_line(fd);
    }
}

int     main(int ac, char **av)
{
    int fd;

    if (ac == 1)
    {
        read_from_fd(0);
        return (0);
    }
    fd = open(av[1], O_RDONLY);
    if (fd == -1)
    {
        printf("fail to open the file\n");
        return (1);
    }
    printf("----------%s-----------\n", av[1]);
    read_from_fd(fd);
    return (0);
}


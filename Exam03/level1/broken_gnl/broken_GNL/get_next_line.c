/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 20:48:45 by chitoupa          #+#    #+#             */
/*   Updated: 2026/02/05 22:21:28 by chitoupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *ft_strchr(char *s, int c)
{
    int i = 0;
    while (s[i])
    {
        if (s[i] == (char)c)
            return ((char *)(s + i));
        i++;
    }
    if (c == '\0')
        return ((char *)(s + i));
    return (NULL);
}

void *ft_memcpy(void *dest, const void *src, size_t n)
{
    size_t    i = 0;

    while (i < n)
    {
        ((char *)dest)[i] = ((char *)src)[i];
        i++;
    }
    return (dest);
}

size_t ft_strlen(char *s)
{
    size_t    res = 0;

    if (!s)
        return (0);
    while (s[res])
        res++;
    return (res);
}

int str_append_mem(char **s1, char *s2, size_t size2)
{
    size_t size1 = ft_strlen(*s1);
    char *newbuff = malloc(size1 + size2 + 1);

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
    size_t  size2 = ft_strlen(s2);

    return str_append_mem(s1, s2, size2);
}

void *ft_memmove(void *dest, const void *src, size_t n)
{
    size_t  i;
    unsigned char *d;
    const unsigned char *s;

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
    char    *line;
    char    *nl;
    static char b[BUFFER_SIZE + 1];
    ssize_t read_ret;

    if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
        return (NULL);
    line = NULL;
    while (1)
    {
        nl = ft_strchr(b, '\n');
        if (nl)
        {
            if (!str_append_mem(&line, b, (size_t)(nl - b + 1)))
                return (free(line), NULL);
            ft_memmove(b, nl + 1, ft_strlen(nl + 1) + 1);
            return (line);
        }
        if (b[0] != '\0')
        {
            if (!str_append_str(&line, b))
                return (free(line), NULL);
            b[0] = '\0';
        }
        read_ret = read(fd, b, BUFFER_SIZE);
        if (read_ret < 0)
        {
            b[0] = '\0';
            return (free(line), NULL); 
        }
        if (read_ret == 0)
        {
            b[0] = '\0';
            if (line && *line)
                return (line);
            return (free(line), NULL);
        }
        b[read_ret] = '\0';
    }
}

#include <stdio.h>
#include <fcntl.h>

void    read_from_fd(int fd)
{
    char *line;

    line = get_next_line(fd);
    while (line)
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
    if (fd < 0)
    {
        perror("Error");
        return (1);
    }
    printf("----------%s----------", av[1]);
    read_from_fd(fd);
    return (0);
}
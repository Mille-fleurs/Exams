/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   broken_gnl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 12:01:25 by chitoupa          #+#    #+#             */
/*   Updated: 2026/02/05 13:01:14 by chitoupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "broken_gnl.h"

static char *ft_strchr(char *str, int c)
{
    int     i;

    if (!str)
        return (NULL);
    i = 0;
    while (str[i])
    {
        if (str[i] == (char)c)
            return (str + i);
        i++;
    }
    if((char)c == '\0')
        return (str + i);
   return (NULL);
}

void    *ft_memcpy(void *dest, void *src, size_t n)
{
    size_t  i;

    i = 0;
    while (i < n)
    {
        ((char *)dest)[i] = ((char *)src)[i];
        i++;
    }
    return (dest);
}

size_t  ft_strlen(char *str)
{
    size_t  len;

    if (!str)
        return (0);
    len = 0;
    while (str[len])
        len++;
    return (len);
}

static void *ft_memmove(void *dest, const void *src, size_t n)
{
    unsigned char *d;
    const unsigned char *s;
    size_t  i;

    if (!dest && !src)
        return (NULL);
    if (dest == src || n == 0)
        return (dest);
    d = (unsigned char)dest;
    s = (const unsigned char)src;
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

static int  append_mem(char **s1, char *s2, size_t size2)
{
    size_t size1;
    char *newbuff;

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

char *get_next_line(int fd)
{
    char *line;
    char *nl;
    ssize_t read_ret;
    static char b[BUFFER_SIZE + 1];

    if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0))
        return (NULL);
    while (1)
    {
        nl = ft_strchr(b, '\n');
        if (nl)
        {
            if (!appned_mem(&line, b, (size_t)(nl - b + 1)))
                return (free(line), NULL);
            ft_memmove(b, nl + 1, ft_strlen(nl + 1) + 1);
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
        {
            b[0] = '\0';
            return (free(line), NULL);
        }
        if (read_ret == 0)
        {
            b[0] = '\0';
            if (line && *line)
                return (line);
            free(line);
            return (NULL);
        }
        b[read_ret] == '\0';
    }
}
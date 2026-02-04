/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 11:45:20 by chitoupa          #+#    #+#             */
/*   Updated: 2026/02/03 19:15:40 by chitoupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filter.h"

static int     is_match(char *hay, char *pat, size_t pat_len)
{
    size_t  i;

    i = 0;
    while (i < pat_len)
    {
        if (hay[i] != pat[i])
            return (0);
        i++;
    }
    return (1);
}

static int    print_n(const char *s, size_t n)
{
    if (n == 0)
        return (0);
    if (printf("%.*s", (int)n, s) < 0)
    {
        perror("Error");
        return (1);
    }
    return (0);
}

static int  print_stars(size_t n)
{
    while (n--)
    {
        if (printf("*") < 0)
        {
            perror("Error");
            return (1);
        }
    }
    return (0);
}

int     ft_filter(char *s)
{
    int read_ret;
    int i;
    int j;
    char buff[BUFFER_SIZE];

    read_ret = read(0, buff, BUFFER_SIZE);
    if (read_ret == -1)
        return (print_error(errno));
    while (read_ret > 0)
    {
        i = 0;
        while (i < read_ret)
        {
            if (is_match(&buff[i], s, strlen(s)))
            {
                j = 0;
                while (i < strlen(s))
                    buff[i++] = '*'; 
            }
            i++;
        }
        write(1, buff, strlen(buff));
        read_ret = read(0, buff, BUFFER_SIZE);
        if (read_ret == -1)
            return (print_error(errno));
    }
    return (1);
}

int main(int ac, char **av)
{
    if (ac != 2)
        return (1);
    return (filter_stream(av[1]));
}



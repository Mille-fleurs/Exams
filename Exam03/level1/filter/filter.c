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

int     is_match(char *s1, char *s2)
{
    unsigned long    i;
    unsigned long  len;

    i = 0;
    len = strlen(s2);
    while (i < len)
    {
        if (s1[i] != s2[i])
            return (0);
        i++;
    }
    return (1);
}

int    print_error(int err)
{
    printf("Error: %s\n", strerror(err));
    return (1);
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
            if (is_match(&buff[i], s))
            {
                j = 0;
                while (i < (int)strlen(s))
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
    char *s;
    unsigned long i;

    if (ac != 2)
        return (1);
    s = malloc(sizeof(char) * (strlen(av[1] + 1)));
    if (!s)
        return (1);
    i = 0;
    while (i < strlen(av[1]))
    {
        s[i] = av[1][i];
        i++;
    }
    ft_filter(s);
    return (0);
}

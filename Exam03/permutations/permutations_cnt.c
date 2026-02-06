/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permutations_cnt.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 13:46:53 by chitoupa          #+#    #+#             */
/*   Updated: 2026/02/06 21:07:45 by chitoupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "permutations_cnt.h"

int     ft_strlen(char *s)
{
    int res = 0;

    if (!s)
        return (0);
    while (s[res])
        res++;
    return (res);
}

void    permu_r(int *cnt, int n, int depth, char *buff)
{
    int     c = 0;

    if (depth == n)
    {
        buff[n] = '\0';
        puts(buff);
        return ;
    }
    while (c < 256)
    {
        if (cnt[c])
        {
            buff[depth] = (char)c;
            --cnt[c];
            permu_r(cnt, n, depth + 1, buff);
            ++cnt[c];
        }
        c++;
    }
}

int     main(int ac, char **av)
{
    int i = 0;
    if (ac == 2 && av[1][0])
    {
        int n = ft_strlen(av[1]);
        int cnt[256] = {0};
        char *buff = malloc(n + 1);
        if (!buff)
            return (1);
        while (i < n)
        {
            ++cnt[(unsigned char)av[1][i]];
            i++;
        }
        permu_r(cnt, n, 0, buff);
        free(buff);
    }
    return (0);
}

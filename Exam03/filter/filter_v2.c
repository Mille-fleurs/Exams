/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_v2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 21:41:09 by chitoupa          #+#    #+#             */
/*   Updated: 2026/02/09 22:02:08 by chitoupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void    ft_filter(char *hay, const char *pat)
{
    int i = 0;
    int pat_len = strlen(pat);
    int j, k;

    while (hay[i])
    {
        j = 0;
        while (pat[j] && hay[i + j] && (hay[i + j] == pat[j]))
            j++;
        if (j == pat_len)
        {
            k = 0;
            while (k < pat_len)
            {
                printf("*");
                k++;
            }
            i += pat_len;
        }
        else
        {
            printf("%c", hay[i]);
            i++;
        }
    }
}

int main(int ac, char **av)
{
    char buff[BUFFER_SIZE];
    char *res = NULL;
    char *tmp;
    int total_read = 0;
    int read_ret;

    if (ac != 2)
        return (1);
    while ((read_ret = read(0, buff, BUFFER_SIZE)) > 0)
    {
        tmp = realloc(res, total_read + read_ret + 1);
        if (!tmp)
        {
            free(res);
            perror("Error");
            return (1);
        }
        res = tmp;
        ft_memmove(res + total_read, buff, (size_t)read_ret);
        total_read += read_ret;
        res[total_read] = '\0';
    }
    if (read_ret < 0)
    {
        perror("Error");
        free(res);
        return (1);
    }
    if (!res)
        return (0);
    ft_filter(res, av[1]);
    free(res);
    return (0);
}

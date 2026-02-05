/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 22:40:55 by chitoupa          #+#    #+#             */
/*   Updated: 2026/02/05 23:49:28 by chitoupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 4096
#endif

int is_match(char *hey, char *pat, size_t n)
{
    size_t  i;

    i = 0;
    while (i < n)
    {
        if (hey[i] != pat[i])
            return (0);
        i++;
    }
    return (1);
}

void    print_n(char *str, size_t n)
{
    if (n > 0)
        printf("%.*s", (int)n, str);
}

void    print_stars(size_t n)
{
    while (n--)
        print("*");
}

void    *ft_memcpy(void *dest, void *src, size_t n)
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

void    update_carry(char **carry, size_t *carry_len, size_t pat_len)
{
    size_t  keep;
    size_t  i;

    if (pat_len <= 0)
    {
        (*carry)[0] = '\0';
        *carry_len = 0;
        return ;
    }
    keep = pat_len - 1;
    if (*carry_len <= keep)
        return ;
    i = 0;
    while (i < keep)
    {
        (*carry)[i] = (*carry)[*carry_len - keep + i];
        i++;
    }
    (*carry)[keep] = '\0';
    *carry_len = keep;
}

int concatenate_mem(char **carry, char *buff, size_t *carry_len, size_t buff_len)
{
    char    *tmp;

    tmp = realloc(*carry, *carry_len + buff_len + 1);
    if (!tmp)
        return (0);
    if (buff_len > 0)
        ft_memcpy(*carry + *carry_len, buff, buff_len);
    *carry_len += buff_len;
    (*carry)[*carry_len] = '\0';
    return (1);
}

int    filter_stream(char *pat)
{
    ssize_t read_ret;
    size_t pat_len;
    size_t carry_len;
    size_t safe_len;
    size_t  i;
    char *carry;
    char b[BUFFER_SIZE];

    carry = malloc(1);
    if (!carry)
        return (perror("Error"), 1);
    carry_len = 0;
    pat_len = strlen(pat);
    while (1)
    {
        read_ret = read(0, b, BUFFER_SIZE);
        if (read_ret < 0)
            return (free(carry), perror("Error"), NULL);
        if (read_ret == 0)
            break;
        if (!concatenate_mem(&carry, b, &carry_len, strlen(b)))
            return (free(carry), perror("Error"), NULL);
        if (pat_len == 0)
        {
            print_n(carry, carry_len);
            carry[0] = '\0';
            carry_len = 0;
            continue;
        }
        if (carry_len >= pat_len)
        {
            safe_len = carry_len - pat_len + 1;
            i = 0;
            while (i < safe_len)
            {
                if (i + pat_len <= safe_len && is_match(carry + i, pat, pat_len))
                {
                    print_stars(pat_len);
                    i += pat_len;
                }
                else
                    printf("%c", carry[i++]);
            }
            update_carry(&carry, &carry_len, pat_len);
        }
    }
    if (pat_len == 0)
        print_n(carry, carry_len);
    else
    {
        i = 0;
        while (i < carry_len)
        {
            if (i + pat_len <= carry_len && is_match(carry + i, pat, pat_len))
            {
                print_stars(pat_len);
                i += pat_len;
            }
            else
                printf("%c", carry[i++]);
        }
    }
    free(carry);
    return (1);
}

int     main(int ac, char **av)
{
    if (ac != 2)
        return (0);
    return (filter_stream(av[1]));
}
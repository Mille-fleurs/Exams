/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 22:40:55 by chitoupa          #+#    #+#             */
/*   Updated: 2026/02/07 20:51:51 by chitoupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1024
#endif

int     is_match(char *hay, char *pat, size_t pat_len)
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

void    print_n(char *s, size_t n)
{
    if (n > 0)
        printf("%.*s", (int)n, s);
}

void    print_stars(size_t n)
{
    while (n--)
        printf("*");
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

void    update_carry(char **carry, size_t *carry_len, size_t pat_len)
{
    size_t  keep;
    size_t  i;

    if (pat_len <= 1)
    {
        *carry_len = 0;
        (*carry)[0] = '\0';
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

int     concatenate_mem(char **carry, size_t *carry_len, char *buff, size_t buff_len)
{
    char    *tmp;

    tmp = realloc(*carry, *carry_len + buff_len + 1);
    if (!tmp)
        return (0);
    *carry = tmp;
    if (buff_len > 0)
        ft_memcpy(*carry + *carry_len, buff, buff_len);
    *carry_len += buff_len;
    (*carry)[*carry_len] = '\0';
    return (1);
}

int     filter_stream(char *pat)
{
    int     read_ret;
    size_t  pat_len;
    size_t  carry_len;
    size_t  safe_len;
    size_t  i;
    char    *carry;
    char    b[BUFFER_SIZE];

    pat_len = strlen(pat);
    carry = malloc(1);
    if (!carry)
        return (perror("Error"), 1);
    carry_len = 0;
    carry[0] = '\0';
    while (1)
    {
        read_ret = read(0, b, BUFFER_SIZE);
        if (read_ret == -1)
            return (perror("Error"), free(carry), 1);
        if (read_ret == 0)
            break;
        if (!concatenate_mem(&carry, &carry_len, b, (size_t)read_ret))
            return (perror("Error"), free(carry), 1);
        if (pat_len == 0)
        {
            print_n(carry, carry_len);
            carry[0] = '\0';
            carry_len = 0;
            continue;
        }
        if (carry_len >= pat_len)
        {
            safe_len = carry_len - (pat_len - 1);
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
        return (1);
    return (filter_stream(av[1]));
}
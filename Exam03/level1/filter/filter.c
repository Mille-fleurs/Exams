/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 11:45:20 by chitoupa          #+#    #+#             */
/*   Updated: 2026/02/04 18:27:38 by chitoupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filter.h"

static int  is_match(char *hay, char *pat, size_t pat_len)
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

static void    print_n(const char *str, size_t n)
{
    if (n > 0)
        printf("%.*s", (int)n, str);
}

static void  print_stars(size_t n)
{
    while (n--)
        printf("*");
}

static void *ft_memcpy(void *dest, void *src, size_t n)
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

static void update_carry(char **carry, char *start, size_t pat_len)
{
    char *tmp;

    tmp = malloc(pat_len);
    if (!tmp)
    {
        free(*carry);
        *carry = NULL;
        return ;
    }
    if (pat_len > 1)
        ft_memcpy(tmp, start, pat_len - 1);
    tmp[pat_len] = '\0';
    free(*carry);
    *carry = tmp;
}

static char *concatnate_mem(char **carry, char *buff, size_t *carry_len, size_t buff_len)
{
    char *tmp;

    *carry_len = strlen(*carry);
    tmp = malloc(*carry_len + buff_len + 1);
    if (!tmp)
        return (NULL);
    if (carry_len > 0)
        ft_memcpy(tmp, *carry, *carry_len);
    if (buff_len > 0)
        ft_memcpy(tmp + *carry_len, buff, buff_len);
    tmp[*carry_len + buff_len] = '\0';
    free(*carry);
    *carry = buff;
    return (tmp);
}

int     filter_stream(char *pat)
{
    ssize_t read_ret;
    size_t  pat_len;
    size_t  carry_len;
    size_t  safe_len;
    char buff[BUFFER_SIZE];
    char carry[BUFFER_SIZE + 1];
    char *data;
    char *ptr;

    pat_len = strlen(pat);
    carry_len = 0;
    while (1)
    {
        read_ret = read(0, buff, BUFFER_SIZE);
        if (read_ret < 0)
            return (perror("Error"), 1);
        if (read_ret == 0)
            break;
        if (pat_len == 0)
            print_n(buff, (size_t)read_ret);
        data = concatnate_mem(&carry, buff, &carry_len, (size_t)read_ret);
        if (!data)
            return (perror("Error"), 1);
        ptr = data;
        safe_len = carry_len + (size_t)read_ret + 1 - pat_len;
        while (safe_len--)
        {
            if (is_match(ptr, pat, pat_len))
                print_stars(pat_len);
            printf("%c", *ptr);
            ptr++;
        }
        update_carry(&carry, ptr, pat_len);
        if (!carry[0])
            return (perror("Error"), 1);
        free(data);
    }
    ptr = carry;
    carry_len = strlen(carry);
    while (*ptr)
    {
        if (is_match(ptr, pat, carry_len))
            print_stars(pat_len);
        printf("%c", *ptr);
        ptr++;
    }
    return (0);
}

int main(int ac, char **av)
{
    if (ac != 2)
        return (1);
    return (filter_stream(av[1]));
}

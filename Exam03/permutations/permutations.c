/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permutations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 22:22:44 by chitoupa          #+#    #+#             */
/*   Updated: 2026/01/29 23:18:46 by chitoupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Assignment name : permutations

// Expected files : *.c *.h
// Allowed functions : puts, malloc, calloc, realloc, free, write
// ---------------------------------------------------------------

// Write a program that will print all the permutations of a string given as argument.

// The solutions must be given in alphabetical order.

// We will not try your program with strings containing duplicates (eg: 'abccd')

// For example this should work:
// $> ./permutations a | cat -e
// a$
// $> ./permutations ab | cat -e
// ab$
// ba$
// $> ./permutations abc | cat -e
// abc$
// acb$
// bac$
// bca$
// cab$
// cba$

#include "permutations.h"

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

void	ft_swap(char *a, char *b)
{
	char	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	ft_putstr(char *str)
{
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
}

// void	init_str(char *str)
// {
// 	int		i = 0;
// 	int		j;

// 	while (str[i])
// 	{
// 		j = 0;
// 		while (str[j])
// 		{

// 		}
// 	}
// }

// void	sort_str_r(char *str, int len)
// {
// 	int	i;

// 	if (i = len)
// 	{
// 		ft_putstr(str);
// 		return ;
// 	}
// 	i = 0;
// 	while (i < len)
// 	{
// 		sort_str_r()
// 	}
// }

int	main(int ac, char **av)
{
	if (ac == 1)
		return (1);
	if (ac < 2)
	{
		ft_putstr(av[1]);
		return (0);
	}
}

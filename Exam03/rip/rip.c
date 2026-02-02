/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rip.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 15:25:12 by chitoupa          #+#    #+#             */
/*   Updated: 2026/02/02 18:29:11 by chitoupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rip.h"

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

void	print_str(char *str, int len)
{
	int	i;

	i = 0;
	while (i < len)
		write(1, &str[i++], 1);
	write(1, "\n", 1);
}

int	is_balanced(char *str, int len)
{
	int	count;

	if (len % 2)
		return (0);
	count = 0;
	while (*str)
	{
		if (*str == '(')
			count++;
		else
		{
			if (count)
				count--;
			else
				return (0);
		}
	}
	if (!count)
		return (1);
	return (0);
}

void	get_solutions(char *str, char *res, int start, int end, int curr,
		int needed_l, int needed_r)
{
	if (start == end)
	{
		print_str(res, end);
		return ;
	}
	if (str[start] == '(')
	{
		if (needed_r > 0)
			res[curr] = '_';
		else
			res[curr] = str[start];
		if (res[curr] == '_')
			needed_r--;
		get_solutions(str, res, start + 1, end, curr + 1, needed_l, needed_r);
	}
	else
	{
		if (needed_l > 0)
			res[curr] = '_';
		else
			res[curr] = str[start];
		if (res[curr] == '_')
			needed_l--;
		get_solutions(str, res, start + 1, end, curr + 1, needed_l, needed_r);
	}
}

void	count_needed(char *str, int *left, int *right)
{
	while (*str)
	{
		if (*str == '(')
			(*right)++;
		else
		{
			if (right)
				(*right)--;
			else
				(*left)++;
		}
		str++;
	}
}

int	main(int ac, char **av)
{
	int len;
	int needed_l;
	int needed_r;
	char *res;

	needed_l = 0;
	needed_r = 0;
	if (ac > 1)
	{
		len = ft_strlen(av[1]);
		if (len == 1)
		{
			write(1, &av[1][0], 1);
			return (0);
		}
		res = malloc(len);
		if (!res)
			return (1);
		if (is_balanced(av[1], len))
		{
			print_str(av[1], len);
			return (0);
		}
		count_needed(av[1], &needed_l, &needed_r);
		get_solutions(av[1], res, 0, len, 0, needed_l, needed_r);
		// printf("%d\n", is_balanced(av[1], len));
		// printf("left:%d, right:%d\n", needed_l, needed_r);
		return (0);
	}
}
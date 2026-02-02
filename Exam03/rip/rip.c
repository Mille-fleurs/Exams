/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rip.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 15:25:12 by chitoupa          #+#    #+#             */
/*   Updated: 2026/02/02 21:41:04 by chitoupa         ###   ########.fr       */
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
		str++;
	}
	if (!count)
		return (1);
	return (0);
}

void	get_solutions(char *str, char *res, int start, int end, int needed_l,
		int needed_r, int balanced)
{
	if (start == end)
	{
		if (!needed_l && !needed_r && !balanced)
			print_str(res, end);
		return ;
	}
	if (str[start] == '(')
	{
		if (needed_l > 0)
		{
			res[start] = '_';
			get_solutions(str, res, start + 1, end, needed_l - 1, needed_r,
				balanced);
		}
		res[start] = str[start];
		get_solutions(str, res, start + 1, end, needed_l, needed_r, balanced
			+ 1);
	}
	else
	{
		if (needed_r > 0)
		{
			res[start] = '_';
			get_solutions(str, res, start + 1, end, needed_l, needed_r - 1,
				balanced);
		}
		if (balanced > 0)
		{
			res[start] = str[start];
			get_solutions(str, res, start + 1, end, needed_l, needed_r, balanced
				- 1);
		}
	}
}

void	count_needed(char *str, int *left, int *right)
{
	while (*str)
	{
		if (*str == '(')
		{
			if (*right)
				(*right)--;
			else
				(*left)++;
		}
		else
		{
			if (*left)
				(*left)--;
			else
				(*right)++;
		}
		str++;
	}
}

int	main(int ac, char **av)
{
	int len;
	int needed_l;
	int needed_r;
	char buff[MAX_LEN];

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
		if (is_balanced(av[1], len))
		{
			print_str(av[1], len);
			return (0);
		}
		count_needed(av[1], &needed_l, &needed_r);
		get_solutions(av[1], buff, 0, len, needed_l, needed_r, 0);
		// printf("%d\n", is_balanced(av[1], len));
		// printf("left:%d, right:%d\n", needed_l, needed_r);
		return (0);
	}
}
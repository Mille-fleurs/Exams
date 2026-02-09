/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rip.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 15:25:12 by chitoupa          #+#    #+#             */
/*   Updated: 2026/02/09 09:17:03 by chitoupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rip.h"

static int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

static void	print_str(char *str, int len)
{
	int	i;

	i = 0;
	while (i < len)
		write(1, &str[i++], 1);
	write(1, "\n", 1);
}

// static int	is_balanced(char *str, int len)
// {
// 	int	count;

// 	if (len % 2)
// 		return (0);
// 	count = 0;
// 	while (*str)
// 	{
// 		if (*str == '(')
// 			count++;
// 		else
// 		{
// 			if (count)
// 				count--;
// 			else
// 				return (0);
// 		}
// 		str++;
// 	}
// 	if (!count)
// 		return (1);
// 	return (0);
// }

static void	get_solutions(char *str, char *res, int start, int end, int needed_l,
		int needed_r, int balance)
{
	if (start == end)
	{
		if (!needed_l && !needed_r && !balance)
			print_str(res, end);
		return ;
	}
	if (str[start] == '(')
	{
		if (needed_l > 0)
		{
			res[start] = ' ';
			get_solutions(str, res, start + 1, end, needed_l - 1, needed_r,
				balance);
		}
		res[start] = '(';
		get_solutions(str, res, start + 1, end, needed_l, needed_r, balance
			+ 1);
	}
	else
	{
		if (needed_r > 0)
		{
			res[start] = ' ';
			get_solutions(str, res, start + 1, end, needed_l, needed_r - 1,
				balance);
		}
		if (balance > 0)
		{
			res[start] = ')';
			get_solutions(str, res, start + 1, end, needed_l, needed_r, balance
				- 1);
		}
	}
}

static void	count_needed(char *str, int *needed_l, int *needed_r)
{
	int open;

	open = 0;
	*needed_l = 0;
	*needed_r = 0;
	while (*str)
	{
		if (*str == '(')
			open++;
		else
		{
			if (open > 0)
				open--;
			else
				(*needed_r)++;
		}
		str++;
	}
	*needed_l = open;
}

int	main(int ac, char **av)
{
	int len;
	int needed_l;
	int needed_r;
	char buff[MAX_LEN];

	if (ac != 2)
		return (1);
	len = ft_strlen(av[1]);
	if (len <= 0)
	{
		write(1, "\n", 1);
		return (0);
	}
	if (len > MAX_LEN)
		return (0);
	count_needed(av[1], &needed_l, &needed_r);
	get_solutions(av[1], buff, 0, len, needed_l, needed_r, 0);
	return (0);
}
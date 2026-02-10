/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_queens.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 14:16:06 by chitoupa          #+#    #+#             */
/*   Updated: 2026/02/09 09:41:37 by chitoupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "n_queens.h"

static int	ft_abs(int num)
{
	if (num < 0)
		return (-num);
	return (num);
}

static void	putnbr_fd(int n, int fd)
{
	char	c;

	if (n >= 10)
		putnbr_fd(n / 10, fd);
	c = n % 10 + '0';
	write(fd, &c, 1);
}

static void	print_set(int *tab, int n)
{
	int		i;

	i = 0;
	while (i < n)
	{
		putnbr_fd(tab[i], 1);
		if (i < n - 1)
			write(1, " ", 1);
		i++;
	}
	write(1, "\n", 1);
}

static int	is_valid_row(int *tab, int row, int col)
{
	int	i;

	i = 0;
	while (i < col)
	{
		if (tab[i] == row)
			return (0);
		if (ft_abs(tab[i] - row) == ft_abs(i - col))
			return (0);
		i++;
	}
	return (1);
}

static void	solve_puzzle(int *tab, int col, int n)
{
	int		row;

	if (col == n)
	{
		print_set(tab, n);
		return ;
	}
	row = 0;
	while (row < n)
	{
		if (is_valid_row(tab, row, col))
		{
			tab[col] = row;
			solve_puzzle(tab, col + 1, n);
		}
		row++;
	}
}

int	main(int ac, char **av)
{
	int	n;
	int	*tab;

	if (ac != 2)
		return (1);
	n = atoi(av[1]);
	if (n <= 0)
		return (0);
	tab = malloc(sizeof(int) * n);
	if (!tab)
		return (1);
	solve_puzzle(tab, 0, n);
	free(tab);
	return (0);
}
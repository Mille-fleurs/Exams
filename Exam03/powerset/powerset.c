/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   powerset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 15:14:36 by chitoupa          #+#    #+#             */
/*   Updated: 2026/02/02 19:47:52 by chitoupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "powerset.h"

static int	check_duplicate(int *str, int len)
{
	int	i;
	int	j;

	i = 0;
	while (i < len - 1)
	{
		j = i + 1;
		while (j < len)
		{
			if (str[i] == str[j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	print_subset(int *tab, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (i < len - 1)
			printf("%d ", tab[i]);
		else
			printf("%d", tab[i]);
		i++;
	}
	printf("\n");
}

void	find_subset(int target, int *tab, int *res, int sum, int start, int end,
		int curr, int *printed)
{
	if (start == end)
	{
		if (sum == target)
		{
			print_subset(res, curr);
			*printed = 1;
		}
		return ;
	}
	find_subset(target, tab, res, sum, start + 1, end, curr, printed);
	res[curr] = tab[start];
	find_subset(target, tab, res, sum + tab[start], start + 1, end, curr + 1, printed);
}

int	main(int ac, char **av)
{
	int i;
	int j;
	int n;
	int *tab;
	int *res;
	int len;
	int	printed;

	if (ac < 2)
	{
		printf("\n");
		return (0);
	}
	len = ac - 2;
	n = atoi(av[1]);
	tab = malloc(sizeof(int) * len);
	if (!tab)
		return (1);
	i = 2;
	j = 0;
	while (i < ac)
	{
		tab[j] = atoi(av[i]);
		i++;
		j++;
	}
	if (!check_duplicate(tab, len))
	{
		free(tab);
		return (1);
	}
	res = malloc(sizeof(int) * len);
	if (!res)
	{
		free(tab);
		return (1);
	}
	printed = 0;
	find_subset(n, tab, res, 0, 0, len, 0, &printed);
	if (!printed)
		printf("\n");
	free(tab);
	free(res);
	return (0);
}
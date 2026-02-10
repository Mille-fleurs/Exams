/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   powerset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 15:14:36 by chitoupa          #+#    #+#             */
/*   Updated: 2026/02/09 21:29:01 by chitoupa         ###   ########.fr       */
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
		if (i > 0)
			printf(" ");
		printf("%d", tab[i]);
		i++;
	}
	printf("\n");
}

void	find_subset(int target, int *set, int *subset, int sum, int start, int end,
		int curr, int *printed)
{
	if (start == end)
	{
		if (sum == target)
		{
			print_subset(subset, curr);
			*printed = 1;
		}
		return ;
	}
	find_subset(target, set, subset, sum, start + 1, end, curr, printed);
	subset[curr] = set[start];
	find_subset(target, set, subset, sum + set[start], start + 1, end, curr + 1, printed);
}

int	main(int ac, char **av)
{
	int i;
	int n;
	int *set;
	int *subset;
	int len;
	int	printed;

	if (ac < 3)
		return (1);
	set = NULL;
	subset = NULL;
	len = ac - 2;
	n = atoi(av[1]);
	if (len > 0)
	{
		set = malloc(sizeof(int) * len);
		if (!set)
			return (1);
		subset = malloc(sizeof(int) * len);
		if (!subset)
			return (free(set), 1);
		i = 0;
		while (i < len)
		{
			set[i] = atoi(av[i + 2]);
			i++;
		}
		if (!check_duplicate(set, len))
			return (free(subset), free(set), 1);
	}
	printed = 0;
	find_subset(n, set, subset, 0, 0, len, 0, &printed);
	if (!printed && n == 0)
		printf("\n");
	free(subset);
	free(set);
	return (0);
}
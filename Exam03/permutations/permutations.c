/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permutations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 22:22:44 by chitoupa          #+#    #+#             */
/*   Updated: 2026/02/05 11:50:02 by chitoupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	sort_str(char *str, int len)
{
	int	i;
	int	j;

	i = 0;
	while (i < len - 1)
	{
		j = i + 1;
		while (j < len)
		{
			if (str[i] > str[j])
				ft_swap(&str[i], &str[j]);
			j++;
		}
		i++;
	}
}

static int	next_perm(char *s, int n)
{
	int i;
	int	j;

	i = n - 2;
	while (i >= 0 && s[i] >= s[i + 1])
		i--;
	if (i < 0)
		return (0);
	j = n - 1;
	while (s[j] <= s[i])
		j--;
	ft_swap(&s[i], &s[j]);
	i++;
	j = n - 1;
	while (i < j)
	{
		ft_swap(&s[i], &s[j]);
		i++;
		j--;
	}
	return (1);
}

// void	permutations_r(char *str, int start, int end)
// {
// 	int	i;

// 	if (start == end - 1)
// 	{
// 		ft_putstr(str);
// 		return ;
// 	}
// 	i = start;
// 	while (i < end)
// 	{
// 		ft_swap(&str[i], &str[start]);
// 		permutations_r(str, start + 1, end);
// 		ft_swap(&str[i], &str[start]);
// 		i++;
// 	}
// }

int	main(int ac, char **av)
{
	int		i;
	int		len;
	char	*dup;

	if (ac != 2)
		return (1);
	len = ft_strlen(av[1]);
	dup = malloc(len + 1);
	if (!dup)
		return (1);
	i = 0;
	while (av[1][i])
	{
		dup[i] = av[1][i];
		i++;
	}
	dup[i] = '\0';
	sort_str(dup, len);
	ft_putstr(dup);
	while (next_perm(dup, len))
		ft_putstr(dup);
	// permutations_r(dup, 0, len);
	free(dup);
	return (0);
}

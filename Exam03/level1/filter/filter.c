/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 11:45:20 by chitoupa          #+#    #+#             */
/*   Updated: 2026/02/03 19:15:40 by chitoupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filter.h"

static int	is_match(char *hay, char *pat, size_t pat_len)
{
	size_t	i;

	i = 0;
	while (i < pat_len)
	{
		if (hay[i] != pat[i])
			return (0);
		i++;
	}
	return (1);
}

static void	print_n(const char *str, size_t n)
{
	if (n > 0)
		printf("%.*s", (int)n, str);
}

static void	print_stars(size_t n)
{
	while (n--)
		printf("*");
}

static void	ft_memcpy(void *dest, void *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)dest)[i] = ((char *)src)[i];
		i++;
	}
}

static void	update_carry(char **carry, size_t *carry_len, size_t pat_len)
{
	size_t	keep;
	size_t	i;

	if (pat_len <= 1)
	{
		(*carry)[0] = '\0';
		*carry_len = 0;
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

static int	concatnate_mem(char **carry, char *buff,
							size_t *carry_len, size_t buff_len)
{
	char	*tmp;

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

int	filter_stream(char *pat)
{
	ssize_t	read_ret;
	size_t	pat_len;
	size_t	carry_len;
	size_t	safe_len;
	size_t	i;
	char	buff[BUFFER_SIZE];
	char	*carry;

	pat_len = strlen(pat);
	carry = malloc(1);
	if (!carry)
		return (perror("Error"), 1);
	carry[0] = '\0';
	carry_len = 0;
	while (1)
	{
		read_ret = read(0, buff, BUFFER_SIZE);
		if (read_ret < 0)
			return (free(carry), perror("Error"), 1);
		if (read_ret == 0)
			break ;
		if (!concatnate_mem(&carry, buff, &carry_len, (size_t)read_ret))
			return (free(carry), perror("Error"), 1);
		if (pat_len == 0)
		{
			print_n(carry, carry_len);
			carry[0] = '\0';
			carry_len = 0;
			continue ;
		}
		if (carry_len >= pat_len)
		{
			safe_len = carry_len - (pat_len - 1);
			i = 0;
			while (i < safe_len)
			{
				if (i + pat_len <= safe_len
					&& is_match(carry + i, pat, pat_len))
				{
					print_stars(pat_len);
					i += pat_len;
				}
				else
				{
					printf("%c", carry[i]);
					i++;
				}
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
			if (i + pat_len <= carry_len
				&& is_match(carry + i, pat, pat_len))
			{
				print_stars(pat_len);
				i += pat_len;
			}
			else
			{
				printf("%c", carry[i]);
				i++;
			}
		}
	}
	free(carry);
	return (0);
}

int	main(int ac, char **av)
{
	if (ac != 2)
		return (1);
	return (filter_stream(av[1]));
}

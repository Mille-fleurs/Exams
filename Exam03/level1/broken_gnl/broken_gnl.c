/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   broken_gnl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 10:30:29 by chitoupa          #+#    #+#             */
/*   Updated: 2026/02/03 18:13:27 by chitoupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "broken_gnl.h"

char	*ft_strchr(char *s, int c)
{
	/*int i = 0;
	while (s[i] != c)
		i++;
	if (s[i] == c)
		return (s + i);
	else
		return (NULL);*/
    int i;

	i = 0;
    while (s[i])
    {
        if (s[i] == c)
            return (s + i);
        i++;
    }
    return (NULL);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
    /*while (--n > 0)
		((char*)dest)[n - 1] = ((char*)src)[n - 1];
	return (dest);*/

    size_t i;

    i = 0;
    while (i < n)
    {
        ((char *)dest)[i] = ((char *)src)[i];
        i++;
    }
    return (dest);
}

size_t  ft_strlen(char *s)
{
    	/*size_t ret = 0;
	while (*s)
	{
		s++;
		ret++;
	}
	return (ret);*/

    size_t ret;

	if (!s)
		return (0);
    ret = 0;
    while(s[ret])
        ret++;
    return (ret);
}

int	str_append_mem(char **s1, char *s2, size_t size2)
{
    /*size_t size1 = ft_strlen(*s1);
	tmp = malloc(size2 + size1 + 1);
	if (!tmp)
		return (0);
	ft_memcpy(tmp, *s1, size1);
	ft_memcpy(tmp + size1, s2, size2);
	tmp[size1 + size2] = 0;
	free(*s1);
	*s1 = tmp;
	return (1);*/

    size_t	size1;
	char	*temp;

	if (*s1)
		size1 = ft_strlen(*s1);
	else
		size1 = 0;
	temp = malloc(size1 + size2 + 1);
	if (!temp)
		return (0);
	if (*s1)
		ft_memcpy(temp, *s1, size1);
	ft_memcpy(temp + size1, *s2, size2);
	temp[size1 + size2] = '\0';
	*s1 = temp;
	free(temp);
	return (1);
}

int	str_append_str(char **s1, char *s2)
{
	size_t	size2;

	size2 = ft_strlen(s2);
	return (str_append_mem(s1, s2, size2));
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (!dest && !src)
		return (NULL);
	if (n == 0)
		return (dest);
	if (dest < src)
		return (ft_memcpy(dest, src, n));
	else if (dest == src)
		return (dest);
	i = n - 1;
	while (i >= 0)
	{
		((char *)dest)[i] = ((char *)src)[i];
		i--;
	}
	return (dest);
	/*if (dest > src)
		return (ft_memcpy(dest, src, n));
	else if (dest == src)
		return (dest);
	i = ft_strlen((char*)src) - 1;
	while (i >= 0)
	{
		((char*)dest)[i] = ((char*)src)[i];
		i--;
	}
	return (dest);*/
}

char	*get_next_line(int fd)
{
	char	*ret;
	char	*tmp;
	int 	read_ret;
	static char b[BUFFER_SIZE + 1];

	ret = NULL;
	while (1)
	{
		tmp = ft_strchr(b, '\n');
		if (tmp)
		{
			if (!str_append_mem(&ret, b, tmp - b + 1))
				return (free(ret), NULL);
			ft_memmove(b, tmp + 1, ft_strlen(b) - (tmp - b + 1));
			return (ret);
		}
		if (!str_append_str(&ret, b))
			return (NULL);
		read_ret = read(fd, b, BUFFER_SIZE);
		if (read_ret <= 0)
		{
			b[0] = '\0';
			if (ret && *ret)
				return (ret);
			free(ret);
			return (NULL);
		}
		b[read_ret] = '\0';
	}
	/*static char b[BUFFER_SIZE + 1] = "";
	ret = NULL;
	tmp = ft_strchr(b, '\n');
	while (!tmp)
	{
		if (!str_append_str(&ret, b))
			return NULL;
		read_ret = read(fd, b, BUFFER_SIZE);
		if (read_ret == -1)
			return NULL;
		b[read_ret] = 0;
	}
	if (!str_append_mem(&ret, b, tmp - b + 1))
	{
		free(ret);
		return NULL;
	}
	return ret;*/
}




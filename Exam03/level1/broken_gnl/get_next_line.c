#include "get_next_line.h"

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return (s + i);
		i++;
	}
	return (NULL);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)dest)[i] = ((char *)src)[i];
		i++;
	}
	return (dest);
}

size_t	ft_strlen(char *s)
{
	size_t	len;

	len = 0;
	if (!s)
		return (0);
	while (s[len] != '\0')
		len++;
	return (len);
}

int	str_append_mem(char **s1, char *s2, size_t size2)
{
	char	*tmp;
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
	ft_memcpy(temp + size1, s2, size2);
	temp[size1 + size2] = '\0';
	free(*s1);
	*s1 = temp;
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
	unsigned char *d;
	const unsigned char	*s;

	if (!dest && !src)
		return (NULL);
	if (dest == src || n == 0)
		return (dest);
	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	if (d < s)
	{
		i = 0;
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
	}
	else
	{
		while (n > 0)
		{
			n--;
			d[n] = s[n];
		}
	}
	return (dest);
}

char	*get_next_line(int fd)
{
	static char	b[BUFFER_SIZE + 1] = "";
	char		*ret;
	char		*temp;
	int			read_ret;

	ret = NULL;
	while (1)
	{
		temp = ft_strchr(b, '\n');
		if (temp)
		{
			if (!str_append_mem(&ret, b, temp - b + 1))
				return (free(ret), NULL);
			ft_memmove(b, temp + 1, ft_strlen(temp + 1) + 1);
			return ret;
		}
		if (!str_append_str(&ret, b))
			return NULL;
		read_ret = read(fd, b, BUFFER_SIZE);
		if (read_ret == -1)
			return (free(ret), NULL);
		if (read_ret == 0)
		{
			b[0] = '\0';
			if (ret && *ret)
				return ret;
			free(ret);
			return NULL;
		}
		b[read_ret] = '\0';
	}
}
/*
int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Uso: %s <arquivo_para_ler>\n", argv[0]);
		return 1;
	}

	// Abrimos argv[1]
	int fd = open(argv[1], O_RDONLY);
	if (fd < 0) // Cubrimos que sea negativo
	{
		perror("Error: no se puede abrir el archivo");
		return 1;
	}

	char *line;
	int count = 0;

	while ((line = get_next_line(fd)) != NULL)
	{
		printf("Linea %d: %s", count + 1, line);
		free(line); // Podemos liberar directamente despues de generarla,
			aunque no se entrega main
		count++;
	}

	close(fd);
	return 0;
}*/
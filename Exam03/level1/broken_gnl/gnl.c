/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 10:33:51 by chitoupa          #+#    #+#             */
/*   Updated: 2026/02/03 10:33:58 by chitoupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"

static char	*join_and_free(char *line, char *chunk, int chunk_len)
{
	int		i;
	int		j;
	int		line_len;
	char	*new_line;

	if (!line)
	{
		line = malloc(1);
		line[0] = '\0';
	}
	line_len = 0;
	while (line[line_len])
		line_len++;
	new_line = malloc(line_len + chunk_len + 1);
	if (!new_line)
	{
		free(line);
		return (NULL);
	}
	i = -1;
	while (++i < line_len)
		new_line[i] = line[i];
	j = -1;
	while (++j < chunk_len)
		new_line[i + j] = chunk[j];
	new_line[i + j] = '\0';
	free(line);
	return (new_line);
}

char	*get_next_line(int fd)
{
	static char buf[BUFFER_SIZE];
	static int bytes_buf;
	static int pos = 0;
	char *line = NULL;
	int found = 0;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);

	while (!found)
	{
		if (pos >= bytes_buf)
		{
			bytes_buf = read(fd, buf, BUFFER_SIZE);
			pos = 0;
			if (bytes_buf <= 0)
				break ;
		}
		int chunk_start = pos;
		while (pos < bytes_buf && buf[pos] != '\n')
			pos++;
		if (pos < bytes_buf && buf[pos] == '\n')
		{
			pos++;
			found = 1;
		}
		line = join_and_free(line, buf + chunk_start, pos - chunk_start);
		if (!line)
			return (NULL);
	}
	if (bytes_buf < 0)
	{
		free(line);
		return (NULL);
	}
	return (line);
}
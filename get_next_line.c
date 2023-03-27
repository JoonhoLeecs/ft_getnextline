/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonhlee <joonhlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 14:41:51 by joonhlee          #+#    #+#             */
/*   Updated: 2023/03/27 18:03:14 by joonhlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	int			rcheck;
	static char	buffer[BUFFER_SIZE];
	char		*line;
	size_t		size;

	size = BUFFER_SIZE;
	if (size == 0)
		return (0);
	rcheck = BUFFER_SIZE;
	line = ft_check_remaining(buffer, &rcheck, size);
	while (rcheck == BUFFER_SIZE)
	{
		rcheck = read(fd, buffer, size);
		line = ft_strjoin_free_gnl(line, buffer, rcheck);
		rcheck = ft_pack_remaining(buffer, rcheck, size, (line == 0));
	}
	return (line);
}

// concaternate buffer at end of line.
//  If line is null ptr, it means start of gnl, just strdup
//  if line isn't null, it's result of malloc, free before return
char	*ft_strjoin_free_gnl(char *line, char *buffer, int rcheck)
{
	size_t	cpy_len;
	size_t	line_len;
	char	*result;

	if (rcheck < 0)
	{
		free(line);
		return (0);
	}
	if (rcheck == 0)
		return (line);
	cpy_len = ft_find_nchr_to_cpy(buffer, rcheck);
	line_len = ft_strlen_gnl(line);
	result = (char *)malloc((line_len + cpy_len + 1) * sizeof(char));
	if (result != 0)
	{
		ft_memmove(result, line, line_len);
		ft_memmove((result + line_len), buffer, cpy_len);
		result[line_len + cpy_len] = '\0';
	}
	free(line);
	return (result);
}

int	ft_pack_remaining(char *buffer, int rcheck, size_t size, int stop)
{
	size_t	cpy_len;
	size_t	i;


	i = 0;
	if (rcheck <= 0 || stop == 1)
	{
		while (i < size)
			buffer[i++] = '\0';
		return (0);
	}
	cpy_len = ft_find_nchr_to_cpy(buffer, rcheck);
	rcheck = cpy_len;
	if ((size_t) rcheck == size && buffer[size - 1] == '\n')
		rcheck = 0;
	while (cpy_len + i < size)
	{
		buffer[i] = buffer[cpy_len + i];
		i++;
	}
	while (i < size)
		buffer[i++] = '\0';
	return (rcheck);
}

// check if remained input from previous call and return parsed
char	*ft_check_remaining(char *buffer, int *rcheck, size_t size)
{
	size_t	buffer_len;
	size_t	cpy_len;
	char	*result;

	if (buffer[0] == '\0')
		return (0);
	buffer_len = ft_strlen_gnl(buffer);
	cpy_len = ft_find_nchr_to_cpy(buffer, buffer_len);
	result = (char *) malloc((cpy_len + 1) * sizeof (char));
	if (result == 0)
		return (0);
	ft_memmove(result, buffer, cpy_len);
	result[cpy_len] = '\0';
	ft_pack_remaining(buffer, (cpy_len < buffer_len) * buffer_len, size, 0);
	if (cpy_len < buffer_len)
		*rcheck = 0;
	return (result);
}

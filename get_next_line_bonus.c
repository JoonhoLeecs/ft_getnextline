/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonhlee <joonhlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 14:41:51 by joonhlee          #+#    #+#             */
/*   Updated: 2023/03/28 18:16:49 by joonhlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static t_remains	*head;
	t_remains			*fd_node;
	int					rcheck;
	char				buffer[BUFFER_SIZE];
	char				*line;

	if (BUFFER_SIZE == 0)
		return (0);
	fd_node = ft_find_create_node(&head, fd);
	if (fd_node == 0)
		return (0);
	rcheck = BUFFER_SIZE;
	line = ft_check_remains(fd_node, &rcheck);
	while (rcheck == BUFFER_SIZE)
	{
		rcheck = read(fd, buffer, BUFFER_SIZE);
		line = ft_strjoin_free_gnl(line, buffer, rcheck);
		rcheck = ft_pack_rmn(buffer, rcheck, fd_node, &line);
	}
	if (line == 0 || fd_node->fd_remains == 0)
		ft_clear_fd_node(&head, fd);
	return (line);
}

// concaternate buffer at end of line.
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
	if (result == 0)
	{
		free(line);
		return (0);
	}
	ft_memmove(result, line, line_len);
	ft_memmove((result + line_len), buffer, cpy_len);
	result[line_len + cpy_len] = '\0';
	free(line);
	return (result);
}

// if whole buffer isn't copied, pack it in fd_node->fd_remain for future use
// return adjusted rcheck to determine to continue or break loop
int	ft_pack_rmn(char *buffer, int rcheck, t_remains *node, char **line)
{
	size_t	cpy_len;
	char	*remains;

	if (rcheck <= 0 || *line == 0)
		return (0);
	cpy_len = ft_find_nchr_to_cpy(buffer, rcheck);
	if (cpy_len < (size_t) rcheck)
	{
		remains = (char *)malloc(rcheck - cpy_len + 1);
		if (remains == 0)
		{
			free(*line);
			*line = 0;
			return (-1);
		}
		ft_memmove(remains, (buffer + cpy_len), rcheck - cpy_len);
		remains[(size_t)rcheck - cpy_len] = '\0';
		node->fd_remains = remains;
	}
	rcheck = cpy_len;
	if ((size_t) rcheck == BUFFER_SIZE && buffer[BUFFER_SIZE - 1] == '\n')
		rcheck = 0;
	return (rcheck);
}

// check if remained input from previous call exist and
// return a new line and pack remains
char	*ft_check_remains(t_remains *fd_node, int *rcheck)
{
	size_t	prev_remain_len;
	size_t	cpy_len;
	char	*result;
	char	*prev_remains;

	prev_remains = fd_node->fd_remains;
	fd_node->fd_remains = 0;
	if (prev_remains == 0)
		return (0);
	prev_remain_len = ft_strlen_gnl(prev_remains);
	cpy_len = ft_find_nchr_to_cpy(prev_remains, prev_remain_len);
	result = (char *) malloc((cpy_len + 1) * sizeof (char));
	if (result == 0)
		return (ft_free_reset(rcheck, prev_remains));
	ft_memmove(result, prev_remains, cpy_len);
	result[cpy_len] = '\0';
	if (ft_pack_rmn(prev_remains, prev_remain_len, fd_node, &result) == -1)
		return (ft_free_reset(rcheck, prev_remains));
	free(prev_remains);
	if (cpy_len < prev_remain_len)
		*rcheck = 0;
	return (result);
}

char	*ft_free_reset(int *rcheck, char *prev)
{
	free(prev);
	*rcheck = 0;
	return (0);
}

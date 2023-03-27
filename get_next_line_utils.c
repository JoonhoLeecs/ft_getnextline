/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonhlee <joonhlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 14:43:27 by joonhlee          #+#    #+#             */
/*   Updated: 2023/03/27 17:36:58 by joonhlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_find_nchr_to_cpy(char *buffer, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		if (buffer[i] == '\n')
			return (i + 1);
		i++;
	}
	return (i);
}

size_t	ft_strlen_gnl(const char *s)
{
	size_t	i;

	if (s == 0)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*ptr_src;
	unsigned char	*ptr_dst;

	i = 0;
	ptr_src = (unsigned char *)src;
	ptr_dst = (unsigned char *)dst;
	if (dst == src)
		return (dst);
	while (i < len)
	{
		if (dst > src)
			*(ptr_dst + len - 1 - i) = *(ptr_src + len - 1 - i);
		else
			*(ptr_dst + i) = *(ptr_src + i);
		i++;
	}
	return ((void *)ptr_dst);
}

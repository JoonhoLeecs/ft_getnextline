/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonhlee <joonhlee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 14:42:35 by joonhlee          #+#    #+#             */
/*   Updated: 2023/03/27 17:37:11 by joonhlee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

char	*get_next_line(int fd);
char	*ft_strjoin_free_gnl(char *line, char *buffer, int rcheck);
int		ft_pack_remaining(char *buffer, int rcheck, size_t size, int stop);
char	*ft_check_remaining(char *buffer, int *rcheck, size_t size);
size_t	ft_find_nchr_to_cpy(char *buffer, size_t size);
size_t	ft_strlen_gnl(const char *s);
void	*ft_memmove(void *dst, const void *src, size_t len);

#endif

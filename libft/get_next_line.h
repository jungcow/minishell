/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungwkim <jungwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 14:58:59 by jungwkim          #+#    #+#             */
/*   Updated: 2021/04/16 22:59:14 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

typedef struct		s_backup
{
	char			*str;
	char			*tmp;
	char			buffer[BUFFER_SIZE];
	ssize_t			sum;
	int				fd;
	struct s_backup	*next;
}					t_backup;

int					get_next_line(int fd, char **line);
t_backup			*find_buffer(int fd, t_backup **backup);
int					read_buffer(int fd, t_backup *ptr, char **line);
int					read_buffer_rest(t_backup *ptr, char **line);
void				clear_buffer(t_backup **backup);
void				del_buffer(int fd, t_backup **backup);
int					check_buffer(char *str, ssize_t len);
int					realloc_buffer(t_backup *backup, ssize_t start_idx,
									ssize_t len);
int					alloc_line(char **line, t_backup *ptr, ssize_t flag);
char				*ft_strndup(char *str, ssize_t idx);
void				*ft_memcpy(void	*dst, const void *src, ssize_t len);

#endif

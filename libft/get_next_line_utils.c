/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungwkim <jungwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 01:10:23 by jungwkim          #+#    #+#             */
/*   Updated: 2021/05/01 04:11:02 by seunghoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char		*ft_strndup(char *str, ssize_t idx)
{
	char	*ptr;
	ssize_t	i;

	i = 0;
	ptr = (char *)malloc(sizeof(char) * (idx + 1));
	if (ptr == NULL || str == NULL)
		return (0);
	while (idx--)
	{
		ptr[i] = str[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

void		*ft_memcpy(void *dst, const void *src, ssize_t len)
{
	char	*destination;
	char	*source;
	ssize_t	i;

	if (!dst && !src)
		return (0);
	destination = (char *)dst;
	source = (char *)src;
	i = -1;
	while (++i < len && source)
		destination[i] = source[i];
	return (dst);
}

t_backup	*find_buffer(int fd, t_backup **backup)
{
	t_backup *ptr;

	ptr = *backup;
	while (ptr)
	{
		if (ptr->fd == fd)
			return (ptr);
		ptr = ptr->next;
	}
	ptr = (t_backup *)malloc(sizeof(t_backup));
	if (ptr == NULL)
		return (NULL);
	ptr->str = NULL;
	ptr->tmp = NULL;
	ptr->sum = 0;
	ptr->fd = fd;
	ptr->next = *backup;
	*backup = ptr;
	return (ptr);
}

int			check_buffer(char *str, ssize_t len)
{
	ssize_t i;

	i = 0;
	while (i < len)
	{
		if (str[i] == 0)
			return (i);
		i++;
	}
	return (-1);
}

int			alloc_line(char **line, t_backup *backup, ssize_t flag)
{
	char *ptr;

	backup->sum -= flag + 1;
	*line = ft_strndup(backup->str, flag);
	if (!(*line))
		return (0);
	ptr = ft_strndup(backup->str + flag + 1, backup->sum);
	if (!ptr)
		return (0);
	free(backup->str);
	backup->tmp = (char *)malloc(sizeof(char) * backup->sum);
	if (!backup->tmp)
		return (0);
	ft_memcpy(backup->tmp, ptr, backup->sum);
	free(ptr);
	return (1);
}

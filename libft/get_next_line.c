/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungwkim <jungwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 16:40:05 by jungwkim          #+#    #+#             */
/*   Updated: 2021/04/16 22:59:34 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>

int			read_buffer(int fd, t_backup *ptr, char **line)
{
	ssize_t				len;
	ssize_t				flag;

	while ((len = read(fd, ptr->buffer, BUFFER_SIZE)) > 0)
	{
		if (!(ptr->str = (char *)malloc(sizeof(char) * (len + ptr->sum))))
			return (-1);
		ft_memcpy(ptr->str, ptr->tmp, ptr->sum);
		free(ptr->tmp);
		ft_memcpy((ptr->str + ptr->sum), ptr->buffer, len);
		ptr->sum += len;
		flag = check_buffer(ptr->str, ptr->sum);
		if (flag >= 0)
		{
			if (!(alloc_line(line, ptr, flag)))
				return (-1);
			return (1);
		}
		if (!(ptr->tmp = ft_strndup(ptr->str, ptr->sum)))
			return (-1);
		free(ptr->str);
	}
	if (len < 0)
		return (-1);
	return (0);
}

int			read_buffer_rest(t_backup *ptr, char **line)
{
	ssize_t	flag;

	if (!(ptr->str = (char *)malloc(sizeof(char) * ptr->sum)))
		return (-1);
	ft_memcpy(ptr->str, ptr->tmp, ptr->sum);
	free(ptr->tmp);
	ptr->tmp = NULL;
	flag = check_buffer(ptr->str, ptr->sum);
	if (flag >= 0)
	{
		if (!(alloc_line(line, ptr, flag)))
			return (-1);
		return (1);
	}
	if (!(*line = ft_strndup(ptr->str, ptr->sum)))
		return (-1);
	free(ptr->str);
	ptr->str = NULL;
	return (0);
}

void		clear_buffer(t_backup **backup)
{
	t_backup *ptr;
	t_backup *tmp;

	ptr = *backup;
	while (ptr)
	{
		tmp = ptr->next;
		free(ptr->str);
		free(ptr->tmp);
		free(ptr);
		ptr = tmp;
	}
	ptr = NULL;
}

void		del_buffer(int fd, t_backup **backup)
{
	t_backup *ptr;
	t_backup *before;

	ptr = *backup;
	if (ptr->fd == fd)
	{
		*backup = ptr->next;
		free(ptr->tmp);
		free(ptr);
		return ;
	}
	while (ptr)
	{
		if (ptr->fd == fd)
		{
			before->next = ptr->next;
			free(ptr->tmp);
			free(ptr);
			break ;
		}
		before = ptr;
		ptr = ptr->next;
	}
}

int			get_next_line(int fd, char **line)
{
	static t_backup		*backup;
	t_backup			*ptr;
	int					flag;
	int					value;

	if (line == 0 || BUFFER_SIZE == 0 || fd < 0)
		return (-1);
	if (!(ptr = find_buffer(fd, &backup)))
		return (-1);
	if ((flag = read_buffer(fd, ptr, line)) == -1)
	{
		clear_buffer(&backup);
		return (-1);
	}
	else if (flag == 1)
		return (1);
	if ((value = read_buffer_rest(ptr, line)) == 1)
		return (1);
	else if (value == -1)
	{
		return (-1);
	}
	del_buffer(fd, &backup);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungwkim <jungwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 16:22:06 by jungwkim          #+#    #+#             */
/*   Updated: 2021/05/04 03:16:25 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "execute/execute.h"

int			treat_pipeline(t_pipeline *pipelines,
								int *new_fd, int *old_fd, int idx)
{
	int				type;

	type = NO_PIPE;
	if (pipelines->length > 1)
		type = HAVE_PIPE;
	if (type == HAVE_PIPE && (idx + 1 < pipelines->length))
	{
		if (dup2(new_fd[WRITE], STDOUT_FILENO) < 0)
			return (-1);
		close_fds(new_fd);
	}
	if (type == HAVE_PIPE && (idx > 0))
	{
		if (dup2(old_fd[READ], STDIN_FILENO) < 0)
			return (-1);
		close_fds(old_fd);
	}
	return (1);
}

int			treat_redirect(t_operation *operation)
{
	int		i;
	int		fd;
	int		last_fd;

	i = 0;
	last_fd = operation->redirects[i].from;
	while (i < operation->len_redirects)
	{
		close(last_fd);
		if (last_fd == STDIN_FILENO)
			fd = open(operation->redirects[i].to, O_CREAT | O_RDONLY, 0644);
		else
		{
			if (operation->redirects[i].is_append == true)
				fd = open(operation->redirects[i].to,
						O_CREAT | O_WRONLY | O_APPEND, 0644);
			else
				fd = open(operation->redirects[i].to, O_CREAT | O_WRONLY, 0644);
		}
		if (fd < 0)
			return (-1);
		last_fd = fd;
		i++;
	}
	return (1);
}

int			execute_child_process(t_pipeline *pipelines,
								int *new_fd, int *old_fd, int idx)
{
	t_operation		*operation;
	char			*dir;

	operation = &pipelines->operations[idx];
	if (get_path(operation, &dir) < 0)
		return (-1);
	if (treat_pipeline(pipelines, new_fd, old_fd, idx) < 0)
		return (-1);
	if (operation->len_redirects)
		if (treat_redirect(operation) < 0)
			return (-1);
	if (execve(dir, operation->argv, g_environ) < 0)
		return (0);
	return (1);
}

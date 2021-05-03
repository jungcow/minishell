/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungwkim <jungwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 16:22:06 by jungwkim          #+#    #+#             */
/*   Updated: 2021/05/04 02:13:33 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute/execute.h"

int			execute_child_process(t_pipeline *pipelines,
								int *new_fd, int *old_fd, int idx)
{
	t_operation		*operation;
	char			*dir;
	int				type;

	type = NO_PIPE;
	if (pipelines->length > 1)
		type = HAVE_PIPE;
	operation = &pipelines->operations[idx];
	if (get_path(operation, &dir) < 0)
		return (-1);
	if (type == HAVE_PIPE && (idx + 1 < pipelines->length))
	{
		dup2(new_fd[WRITE], STDOUT_FILENO);
		close_fds(new_fd);
	}
	if (type == HAVE_PIPE && (idx > 0))
	{
		dup2(old_fd[READ], STDIN_FILENO);
		close_fds(old_fd);
	}
	if (execve(dir, operation->argv, g_environ) < 0)
		return (0);
	return (1);
}

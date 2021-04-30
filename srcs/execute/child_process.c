/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungwkim <jungwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 16:22:06 by jungwkim          #+#    #+#             */
/*   Updated: 2021/05/01 07:17:34 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute/execute.h"

extern char	**environ;

int			execute_child_process(t_pipeline *pipelines,
								int *new_fd, int *old_fd, int idx)
{
	t_operation	*operation;
	char			*dir;
	int				type;
	
	type = NO_PIPE;
	if (pipelines->length > 1)
		type = HAVE_PIPE;
	operation = &pipelines->operations[idx];
	dir = get_path(operation);
	if (dir == NULL)
		return (0);
	if (idx + 1 < pipelines->length && type == HAVE_PIPE)
	{
		dup2(new_fd[WRITE], STDOUT_FILENO);
		close_fds(new_fd);
	}
	if (idx > 0 && type == HAVE_PIPE)
	{
		dup2(old_fd[READ], STDIN_FILENO);
		close_fds(old_fd);
	}
	if (execve(dir, operation->argv, environ) < 0)
		return (0);
	return (1);
}

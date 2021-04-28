/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungwkim <jungwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 19:09:36 by jungwkim          #+#    #+#             */
/*   Updated: 2021/04/28 19:31:49 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipeline/pipeline.h"

int		run_child_process(t_pipeline *pipeline, int *fd, int *old_fd, int idx)
{
	char		*dir;

	dir = parse_path(pipeline->operations->argv[0]);
	if (dir == NULL)
		return (0);
	dir = ft_strjoin(dir, pipeline->operations->argc[0]);
	if (dir == NULL)
		return (0);
	if (idx > 0)
	{
		close(old_fd[1]);
		dup2(old_fd[0], 0);
		close(old_fd[0]);
	}
	if (idx + 1 < pipeline->length)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		close(fd[1]);
	}
	if (!execve(dir, pipeline->operations->argv, NULL) < 0)
		return (0);
}

int		run_process(t_pipeline *pipeline)
{
	pid_t	*pid;
	int		fd[2];
	int		old_fd[2];
	int		idx;

	pid = (t_pid *)malloc(sizeof(t_pid) * pipeline->length);
	if (pid == NULL)
		return (0);
	idx = -1;
	while (++idx < pipeline->length)
	{
		if (pipe(fd) < 0)
			return (0);
		pid[idx] = fork();
		if (pid[idx] < 0)
			return (0);
		else if (pid[idx] == 0)
			if (!run_child_process(pipeline fd, old_fd, idx))
				return (0);
		pipeline->operations = pipeline->operation->next;
		old_fd[0] = fd[0];
		old_fd[1] = fd[1];
	}
	close(fd[0]);
	close(fd[1]);
	while (idx--)
		waitpid(pid[command_num - idx], &status, 0);
}

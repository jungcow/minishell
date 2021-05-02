/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungwkim <jungwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 03:21:12 by jungwkim          #+#    #+#             */
/*   Updated: 2021/05/02 15:42:22 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "execute/execute.h"

int		create_process(pid_t **process, int num)
{
	*process = (pid_t *)malloc(sizeof(pid_t) * num);
	if (*process == NULL)
		return (0);
	return (1);
}

int		wait_process(pid_t *process, int num)
{
	int		status;
	int		i;

	i = 0;
	while (i < num)
	{
		waitpid(process[i], &status, 0);
		printf("child[%d] (PID=%d) finished; ", i, process[i]);
		if (WIFEXITED(status))
			printf("Exit, status=%d\n", WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
			printf("Signal, sig=%d\n", WTERMSIG(status));
		else
			printf("Abnormal exit\n");
		i++;
	}
	return (0);
}

int		execute_process(pid_t *process, t_pipeline *pipelines)
{
	int		i;
	int		new_fd[2];
	int		old_fd[2];

	i = -1;
	while (++i < pipelines->length)
	{
		if ((pipelines->length > 1) && (pipe(new_fd) < 0))
			return (0);
		process[i] = fork();
		if (process[i] < 0)
			return (0);
		if (process[i] == 0 &&
				!execute_child_process(pipelines, new_fd, old_fd, i))
			return (0);
		else if (process[i] > 0 && (i > 0) && (pipelines->length > 1))
			close_fds(old_fd);
		old_fd[0] = new_fd[0];
		old_fd[1] = new_fd[1];
	}
	close_fds(old_fd);
	if (wait_process(process, i) < 0)
		return (0);
	return (1);
}

void	clear_process(pid_t **process)
{
	free(*process);
}

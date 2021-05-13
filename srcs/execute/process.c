/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungwkim <jungwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 03:21:12 by jungwkim          #+#    #+#             */
/*   Updated: 2021/05/13 16:51:46 by seunghoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <sys/wait.h>
#include "execute/execute.h"
#include "command/command.h"

extern t_command	g_command;

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

	i = -1;
	while (++i < num)
	{
		waitpid(process[i], &status, 0);
		if ((unsigned char)status == 0)
			g_command.exit_status = (unsigned char)(status >> 8);
	}
	if ((unsigned char)(status >> 8) == 0)
	{
		if ((((unsigned char)status) & 127) == SIGINT)
		{
			write(1, "\n", 1);
			g_command.exit_status = 130;
		}
		else if ((((unsigned char)status) & 127) == SIGQUIT)
		{
			write(1, "Quit: 3\n", ft_strlen("Quit : 3\n"));
			g_command.exit_status = 131;
		}
	}
	g_command.pid = 0;
	return (0);
}

int		fork_process(pid_t *process, t_pipeline *pipelines,
												int (*fd)[2], int index)
{
	*process = fork();
	if (*process < 0)
		exit(EXIT_FAILURE);
	if (*process > 0)
		g_command.pid = 1;
	if (*process == 0 &&
			execute_child_process(pipelines, fd[NEW], fd[OLD], index) < 0)
		return (-1);
	else if (*process > 0 && (index > 0) && (pipelines->length > 1))
		close_fds(fd[OLD]);
	return (1);
}

int		execute_process(pid_t *process, t_pipeline *pipelines)
{
	int		i;
	int		fd[2][2];

	i = -1;
	while (++i < pipelines->length)
	{
		if ((pipelines->length > 1) && (pipe(fd[NEW]) < 0))
			return (0);
		if (fork_process(&process[i], pipelines, fd, i) < 0)
			return (-1);
		fd[OLD][0] = fd[NEW][0];
		fd[OLD][1] = fd[NEW][1];
	}
	if (pipelines->length > 1)
		close_fds(fd[OLD]);
	if (wait_process(process, i) < 0)
		return (-1);
	return (1);
}

void	clear_process(pid_t **process)
{
	free(*process);
}

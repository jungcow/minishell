/* ************************************************************************** */ /*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungwkim <jungwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 16:47:34 by jungwkim          #+#    #+#             */
/*   Updated: 2021/04/27 21:33:27 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h>
#include "pipeline/pipeline.h"

int		pipe_error(int err)
{
	printf("%s\n", strerror(err));
}

int		has_file(char *path, char *filename)
{
	DIR				*dir;
	struct dirent	*entry;

	dir = opendir(path[idx]);
	if (dir == NULL)
		return (0);
	while (entry = readdir(dir))
		if (ft_strcmp(entry->d_name, filename) == 0)
			return (1);
	return (0);
}

int		check_parse_necessary(char *filename)
{
	struct stat	dump;
	char		*command;
	char		*
	int			i;

	command = filename;
	i = ft_strlen(command);
	while (command[--i])
	{
		if (command[i] == '/')
		{
			command[i] = '\0';
			if (stat(command, &dump) != -1)
				if (has_file(command, filename))
					return (1);
				else
					break ;
			else
				break ;
		}
	}
	return (0);
}

char	*parse_path(char *filename)
{
	char	**path;
	char	*tmp;
	int		i;

	path = ft_split(getenv("PATH"), ':');
	if (path == NULL)
		return (NULL);
	if (check_parse_necessary(filename))
		return (ft_strdup(""));
	i = -1;
	while (path[++i])
		if (has_file(path[i], filename))
		{
			tmp = ft_strdup(path[i]);
			if (tmp == NULL)
				return (NULL);
			break;
		}
	i = -1;
	while (path[++i])
		free(path[i]);
	free(path);
	return (tmp);
}

int		run_child_process(t_pipeline *pipeline, int *fd, int idx)
{
	char	*dir;
	char	*input;
	char	*ouput;

	if (idx == 0)
	{
		close(fd[0]);
	}
	dir = parse_path(pipeline->operation->name);
	dir = ft_strjoin(dir, pipeline->operation->name);
	if (dir == NULL)
		return (0);
	dup2()
}

int		run_xx(t_pipeline *pipeline)
{
	int		fd[2];
	pid_t	*pid;
	int		idx;

	if (!pipeline || !pipeline->operation || !pipeline->length)
		return (0);
	if (pipe(fd) < 0)
		return (0);
	pid = (t_pid *)malloc(sizeof(t_pid) * pipeline->length);
	if (pid == NULL)
		return (0);
	idx = -1;
	while (++idx < pipeline)
	{
		pid[i] = fork();
		if (pid[i] < 0)
			return (0);
		else if (pid[idx] == 0)
		{
			run_child_process(pipeline, fd, idx);
		}
	}
}

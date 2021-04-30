/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungwkim <jungwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 04:51:02 by jungwkim          #+#    #+#             */
/*   Updated: 2021/05/01 07:16:50 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <dirent.h>
#include "execute/execute.h"

int		has_file(char *path, char *filename)
{
	DIR				*dir;
	struct dirent	*entry;

	dir = opendir(path);
	if (dir == NULL)
		return (0);
	while ((entry = readdir(dir)))
	{
		if (ft_strcmp(entry->d_name, filename) == 0)
		{
			closedir(dir);
			return (1);
		}
	}
	closedir(dir);
	return (0);
}

int		check_parse_necessary(char *filename)
{
	struct stat	dump;
	char		*command;
	int			i;

	command = filename;
	i = ft_strlen(command);
	while (command[--i])
	{
		if (command[i] == '/')
		{
			command[i] = '\0';
			if (stat(command, &dump) < 0)
				return (0);
			if (has_file(command, filename))
				return (1);
			break ;
		}
	}
	return (0);
}

char	*parse_path(char *filename)
{
	char	**path;
	char	*dir;
	int		i;

	path = ft_split(getenv("PATH"), ':');
	if (path == NULL)
		return (NULL);
	if (check_parse_necessary(filename))
		return (ft_strdup(""));
	i = -1;
	while (path[++i])
	{
		if (has_file(path[i], filename))
		{
			dir = ft_strdup(path[i]);
			if (dir == NULL)
				return (NULL);
			break ;
		}
	}
	i = -1;
	while (path[++i])
		free(path[i]);
	free(path);
	return (dir);
}

char	*get_path(t_operation *operation)
{
	char	*dir;

	dir = parse_path(operation->argv[0]);
	if (dir == NULL)
		return (NULL);
	dir = ft_strjoin(dir, operation->argv[0]);
	if (dir == NULL)
		return (NULL);
	return (dir);
}

void	close_fds(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}

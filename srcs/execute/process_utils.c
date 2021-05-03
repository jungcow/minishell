/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungwkim <jungwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 04:51:02 by jungwkim          #+#    #+#             */
/*   Updated: 2021/05/04 02:16:57 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <dirent.h>
#include "execute/execute.h"
#include "error/error.h"
#include "libft.h"

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
		if (i == 0)
			break ;
	}
	return (0);
}

int		parse_path(char *filename, char **dir)
{
	char	**path;
	int		i;

	*dir = NULL;
	path = ft_split(getenv("PATH"), ':');
	if (path == NULL)
		return (-1);
	if (check_parse_necessary(filename))
	{
		if (dup_str(dir, "") < 0)
			return (-1);
		return (0);
	}
	i = -1;
	while (path[++i])
		if (has_file(path[i], filename))
		{
			if (dup_str(dir, path[i]) < 0)
				return (-1);
			clear_strs(path);
			return (1);
		}
	clear_strs(path);
	return (0);
}

int		get_path(t_operation *operation, char **dir)
{
	int		ret;

	ret = parse_path(operation->argv[0], dir);
	if (ret == 0)
	{
		command_not_found(operation->argv[0]);
		return (0);
	}
	*dir = ft_strjoin(*dir, "/");
	if (*dir == NULL)
		return (-1);
	*dir = ft_strjoin(*dir, operation->argv[0]);
	if (*dir == NULL)
		return (-1);
	return (1);
}

void	close_fds(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungwkim <jungwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 19:29:41 by jungwkim          #+#    #+#             */
/*   Updated: 2021/04/28 19:30:30 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipeline/pipeline.h"

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

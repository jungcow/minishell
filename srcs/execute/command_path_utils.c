/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_path_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungwkim <jungwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 03:25:31 by jungwkim          #+#    #+#             */
/*   Updated: 2021/05/06 03:29:57 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <dirent.h>
#include "execute/execute.h"
#include "libft.h"

int		check_path_validation(char *command)
{
	struct stat	buf;
	int			type;
	int			permission;

	if (stat(command, &buf) < 0)
		return (NO_SUCH);
	type = buf.st_mode & 0xF000;
	permission = buf.st_mode & 0777;
	if ((permission / 0100) % 2 == 0 ||
			(permission / 010) % 2 == 0 || (permission / 01) % 2 == 0)
		return (PERMISSION);
	if (type == DIRECTORY)
		return (DIRECTORY);
	return (1);
}

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

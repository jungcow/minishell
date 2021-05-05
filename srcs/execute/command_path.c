/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungwkim <jungwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 02:32:32 by jungwkim          #+#    #+#             */
/*   Updated: 2021/05/06 03:33:29 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute/execute.h"
#include "error/error.h"
#include "libft.h"

int		check_path_type(char *command)
{
	if (*command == '/')
		return (*command);
	if (*command == '.')
		return (*command);
	return (0);
}

int		check_path_env(char *filename, char **dir)
{
	char	**path;
	char	**ptr;

	path = ft_split(getenv("PATH"), ':');
	if (path == NULL)
		return (-1);
	ptr = path;
	while (path)
	{
		if (has_file(*path, filename))
			break ;
		path++;
	}
	if (path == NULL)
		clear_strs(ptr);
	if (dup_str(dir, *path) < 0)
		return (-1);
	clear_strs(ptr);
	*dir = ft_strjoin(*dir, "/");
	if (*dir == NULL)
		return (-1);
	*dir = ft_strjoin(*dir, filename);
	if (*dir == NULL)
		return (-1);
	return (1);
}

int		check_path(char *command, char **dir)
{
	int			ret;

	ret = check_path_validation(command);
	if (ret == 1)
		*dir = command;
	return (ret);
}

int		get_path(t_operation *operation, char **dir)
{
	int		ret;

	ret = 1;
	if (check_path_type(operation->argv[0]) == 0)
		ret = check_path_env(operation->argv[0], dir);
	else if (check_path_type(operation->argv[0]) == '/')
		ret = check_path(operation->argv[0], dir);
	else if (check_path_type(operation->argv[0]) == '.')
		ret = check_path(operation->argv[0], dir);
	if (ret == 0 || ret == DIRECTORY || ret == PERMISSION || ret == NO_SUCH)
	{
		command_error(operation->argv[0], ret);
		return (0);
	}
	else if (ret == -1)
		return (-1);
	return (1);
}

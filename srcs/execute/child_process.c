/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungwkim <jungwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 16:22:06 by jungwkim          #+#    #+#             */
/*   Updated: 2021/05/10 18:33:08 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "execute/execute.h"
#include "environ/environ.h"
#include "command/command.h"

extern t_command	g_command;

int			treat_pipeline(t_pipeline *pipelines,
								int *new_fd, int *old_fd, int idx)
{
	int				type;

	type = NO_PIPE;
	if (pipelines->length > 1)
		type = HAVE_PIPE;
	if (type == HAVE_PIPE && (idx + 1 < pipelines->length))
	{
		if (dup2(new_fd[WRITE], STDOUT_FILENO) < 0)
			return (-1);
		close_fds(new_fd);
	}
	if (type == HAVE_PIPE && (idx > 0))
	{
		if (dup2(old_fd[READ], STDIN_FILENO) < 0)
			return (-1);
		close_fds(old_fd);
	}
	return (1);
}

int			treat_redirect(t_operation *operation)
{
	int		i;
	int		last_fd;

	i = 0;
	last_fd = operation->redirects[i].from;
	while (i < operation->len_redirects)
	{
		close(last_fd);
		if (last_fd == STDIN_FILENO)
			last_fd = open(operation->redirects[i].to,
					O_CREAT | O_RDONLY, 0644);
		else
		{
			if (operation->redirects[i].is_append == true)
				last_fd = open(operation->redirects[i].to,
						O_CREAT | O_WRONLY | O_APPEND, 0644);
			else
				last_fd = open(operation->redirects[i].to,
						O_CREAT | O_WRONLY | O_TRUNC, 0644);
		}
		if (last_fd < 0)
			return (-1);
		i++;
	}
	return (last_fd);
}

int			implement_child_process(t_operation *operation,
									char *dir, int redirect_fd)
{
	int		exit_status;
	char	**env;

	if (list_to_strs_environ(g_command.environ, &env) < 0)
		return (-1);
	if (is_builtin(operation->argv[0]))
		exit_status = ft_execve(operation->argv[0],
								operation->argv, &g_command.environ);
	else
		exit_status = execve(dir, operation->argv, env);
	if (exit_status < 0)
		exit(EXIT_FAILURE);
	if (operation->len_redirects)
		close(redirect_fd);
	ft_strsfree(env);
	return (exit_status);
}

int			execute_child_process(t_pipeline *pipelines,
								int *new_fd, int *old_fd, int idx)
{
	t_operation		*operation;
	char			*dir;
	int				redirect_fd;
	int				ret;

	operation = &pipelines->operations[idx];
	ret = !is_builtin(operation->argv[0]) && get_path(operation, &dir);
	if (ret < 0)
		exit(ret);
	if (treat_pipeline(pipelines, new_fd, old_fd, idx) < 0)
		return (-1);
	redirect_fd = 0;
	if (operation->len_redirects)
	{
		redirect_fd = treat_redirect(operation);
		if (redirect_fd < 0)
			return (-1);
	}
	if (!is_builtin(operation->argv[0]) && ret)
	{
		close(redirect_fd);
		exit(ret);
	}
	exit(implement_child_process(operation, dir, redirect_fd));
	return (1);
}

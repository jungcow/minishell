/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungwkim <jungwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 03:49:47 by jungwkim          #+#    #+#             */
/*   Updated: 2021/05/10 20:04:07 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "execute/execute.h"
#include "command/command.h"

extern t_command	g_command;

int		implement_unit_process(t_operation *operation, int redirect_fd)
{
	if (!ft_strcmp(operation->argv[0], "exit"))
		write(1, "exit\n", 5);
	if (ft_execve(operation->argv[0],
				operation->argv, &g_command.environ) < 0)
		return (-1);
	if (operation->len_redirects)
	{
		close(redirect_fd);
		if (open("/dev/tty", O_WRONLY | O_RDONLY) < 0)
			return (-1);
	}
	return (1);
}

int		execute_unit_process(pid_t *process, t_pipeline *pipeline)
{
	t_operation		*operation;
	int				redirect_fd;

	redirect_fd = 0;
	operation = &pipeline->operations[0];
	if (is_builtin(operation->argv[0]))
	{
		if (operation->len_redirects)
		{
			redirect_fd = treat_redirect(operation);
			if (redirect_fd < 0)
				return (-1);
		}
		if (implement_unit_process(operation, redirect_fd) < 0)
			exit(1);
	}
	else if (execute_process(process, pipeline) < 0)
		return (-1);
	return (1);
}

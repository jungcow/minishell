/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungwkim <jungwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 03:49:47 by jungwkim          #+#    #+#             */
/*   Updated: 2021/05/07 22:14:35 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute/execute.h"
#include "command/command.h"

extern t_command	g_command;

int		execute_unit_process(pid_t *process, t_pipeline *pipeline)
{
	t_operation		*operation;

	operation = &pipeline->operations[0];
	if (is_builtin(operation->argv[0]))
	{
		if (!ft_strcmp(operation->argv[0], "exit"))
			write(1, "exit\n", 5);
		if (ft_execve(operation->argv[0], operation->argv, g_command.environ) < 0)
			return (-1);
		return (1);
	}
	if (execute_process(process, pipeline) < 0)
		return (-1);
	return (1);
}

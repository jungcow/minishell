/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungwkim <jungwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 19:09:36 by jungwkim          #+#    #+#             */
/*   Updated: 2021/05/10 16:10:26 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute/execute.h"
#include <errno.h>
#include "command/command.h"

extern t_command	g_command;

int		execute_instruction(t_instruction *instruction)
{
	pid_t		*process;
	int			i;

	i = 0;
	while (i < instruction->length)
	{
		g_command.pid = 0;
		if (check_environ(&instruction->pipelines[i]) < 0)
			return (-1);
		process = NULL;
		if (create_process(&process, instruction->pipelines[i].length) < 0)
			return (-1);
		if (instruction->pipelines[i].length == 1 &&
				execute_unit_process(process, &instruction->pipelines[i]) < 0)
			return (-1);
		else if (instruction->pipelines[i].length > 1 &&
				execute_process(process, &instruction->pipelines[i]) < 0)
			return (-1);
		clear_process(&process);
		i++;
	}
	return (1);
}

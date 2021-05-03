/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungwkim <jungwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 19:09:36 by jungwkim          #+#    #+#             */
/*   Updated: 2021/05/04 00:46:52 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute/execute.h"

int		execute_instruction(t_instruction *instruction)
{
	pid_t		*process;
	int			i;

	i = 0;
	while (i < instruction->length)
	{
		if (check_environ(instruction->pipelines) < 0)
			return (0);
		process = NULL;
		if (create_process(&process, instruction->pipelines[i].length) < 0)
			return (0);
		if (execute_process(process, &instruction->pipelines[i]) < 0)
			return (0);
		clear_process(&process);
		i++;
	}
	return (1);
}

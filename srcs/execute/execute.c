/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungwkim <jungwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 19:09:36 by jungwkim          #+#    #+#             */
/*   Updated: 2021/05/02 20:50:51 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute/execute.h"
#include <stdio.h>
int		execute_instruction(t_instruction *instruction)
{
	pid_t		*process;
	int			i;

	i = 0;
	while (i < instruction->length)
	{
		if (!check_envset(instruction->pipelines))
			return (0);
		process = NULL;
		if (!create_process(&process, instruction->pipelines[i].length))
			return (0);
		if (!execute_process(process, &instruction->pipelines[i]))
			return (0);
		clear_process(&process);
		i++;
	}
	return (1);
}

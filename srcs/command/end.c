/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoh <seunghoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 16:26:27 by seunghoh          #+#    #+#             */
/*   Updated: 2021/04/20 23:23:58 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "command/command.h"

int		apply_end_key(t_command *command, int key)
{
	char	ch;

	if (key == ENTER)
	{
		while (delete_string(&(*command->command_line)->temp, 0, &ch))
			add_string(&(*command->command_line)->line, (*command->command_line)->line.length, ch);
		printf("\n\nResult : [");
		for(int i=0; i < (*command->command_line)->line.length; ++i)
			printf("%c", (*command->command_line)->line.content[i]);
		printf("]\n\n\n");
		//(*command->command_line)->cursor = 0;
		//(*command->command_line)->length = 0;
		if (!add_history(command))
		{
			clear_historylist(command->head);
			return (-1);
		}
		return (0);
	}
	return (1);
}

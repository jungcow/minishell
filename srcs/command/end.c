/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoh <seunghoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 16:26:27 by seunghoh          #+#    #+#             */
/*   Updated: 2021/04/16 17:35:25 by seunghoh         ###   ########.fr       */
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
		while (delete_string(&command->temp, 0, &ch))
			add_string(&command->line, command->line.length, ch);
		printf("\n\nResult : [");
		for(int i=0; i < command->line.length; ++i)
			printf("%c", command->line.content[i]);
		printf("]\n\n\n");
		//command->cursor = 0;
		//command->length = 0;
		return (0);
	}
	return (1);
}

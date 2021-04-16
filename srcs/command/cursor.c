/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoh <seunghoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 14:50:41 by seunghoh          #+#    #+#             */
/*   Updated: 2021/04/16 17:00:56 by seunghoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "command/command.h"

int		apply_cursor_key(t_command *command, int key)
{
	char	ch;

	if (command->cursor != 0 && key == LEFT_ARROW)
	{
		delete_string(&command->line, command->line.length - 1, &ch);
		if (!add_string(&command->temp, 0, ch))
			return (-1);
		command->cursor--;
		write(1, &key, sizeof(key));
	}
	else if (command->cursor != command->length && key == RIGHT_ARROW)
	{
		delete_string(&command->temp, 0, &ch);
		if (!add_string(&command->line, command->line.length, ch))
			return (-1);
		command->cursor++;
		write(1, &key, sizeof(key));
	}
	return (1);
}

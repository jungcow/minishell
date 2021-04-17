/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoh <seunghoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 14:50:41 by seunghoh          #+#    #+#             */
/*   Updated: 2021/04/17 17:36:24 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <termcap.h>
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

int		apply_history_key(t_command *command, int key)
{
	static t_history	**ptr;
	static int			bottom;
	int					flag;

	ptr = command->head;
	flag = 0;
	if (*(command->head) == NULL)
		write_historyline(command, "", 2);
	else
	{
		get_history(ptr, &bottom, &flag, key);
		write_historyline(command, (*ptr)->str, flag);
	}
	return (1);
}

int		apply_delete_key(t_command *command, int key)
{
	char	*dc;
	char	ch;

	// should fix
	key++;
	apply_cursor_key(command, LEFT_ARROW);
	delete_string(&command->temp, 0, &ch);
	dc = tgetstr("dc", NULL);
	tputs(dc, 1, tputs_wrapper);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungwkim <jungwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 23:17:49 by jungwkim          #+#    #+#             */
/*   Updated: 2021/04/21 23:49:00 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <termcap.h>
#include "command/command.h"

int		apply_cursor_key(t_command *command, t_term *term, int key)
{
	char		ch;
	t_history	*ptr;

	ptr = *command->command_line;
	init_term_size(command, term);
	if ((ptr->cursor > 0) && key == LEFT_ARROW)
	{
		delete_string(&ptr->line, ptr->line.length - 1, &ch);
		if (!add_string(&ptr->temp, 0, ch))
			return (-1);
		ptr->cursor--;
		write(1, &key, sizeof(key));
	}
	else if ((ptr->cursor < ptr->length) && key == RIGHT_ARROW)
	{
		delete_string(&ptr->temp, 0, &ch);
		if (!add_string(&ptr->line, ptr->line.length, ch))
			return (-1);
		ptr->cursor++;
		if (term->pos.cur_col == term->pos.col - 1)
			tputs(tgoto(term->cp.cm, 0, ++term->pos.cur_row), 1, tputs_wrapper);
		else
			write(1, &key, sizeof(key));
	}
	return (1);
}

int		apply_history_key(t_command *command, t_term *term, int key)
{
	static t_history	**ptr;
	static int			bottom;
	int					flag;

	ptr = command->head;
	flag = 0;
	if (*(command->head) == NULL)
		write_historyline(command, term, NULL, 2);
	else
	{
		get_history(ptr, &bottom, &flag, key);
		write_historyline(command, term, (*ptr), flag);
		if (flag == 2)
			command->command_line = &command->present;
		else
			command->command_line = ptr;
	}
	return (1);
}

int		apply_delete_key(t_command *command, t_term *term)
{
	char	dump;

	init_term_size(command, term);
	if ((*command->command_line)->line.length <= 0)
		return (1);
	if (apply_cursor_key(command, term, LEFT_ARROW) == -1)
		return (-1);
	delete_string(&(*command->command_line)->temp, 0, &dump);
	tputs(term->cp.dc, 1, tputs_wrapper);
	refresh_command(command, term);
	(*command->command_line)->length--;
	return (1);
}

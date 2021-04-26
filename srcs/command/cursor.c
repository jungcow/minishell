/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungwkim <jungwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 23:17:49 by jungwkim          #+#    #+#             */
/*   Updated: 2021/04/26 20:11:45 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <termcap.h>
#include "command/command.h"

int		apply_ctrlcursor_key(t_command *command, t_term *term, int key)
{
	int		flag;

	flag = 1;
	init_term_size(command, term);
	if ((command->cursor > 0) && key == CTRL_LEFT)
		flag = move_cursor_wordby(command, term, key);
	else if ((command->cursor < command->length) && key == CTRL_RIGHT)
		flag = move_cursor_wordby(command, term, key);
	else if ((command->line.length / term->pos.col) && key == CTRL_UP)
		flag = move_cursor_lineby(command, term, key);
	else if ((command->temp.length / term->pos.col) && key == CTRL_DOWN)
		flag = move_cursor_lineby(command, term, key);
	return (flag);
}

int		apply_multicursor_key(t_command *command, t_term *term, int key)
{
	int		len;

	if ((command->cursor > 0) && (key == HOME))
	{
		len = command->line.length;
		while (len--)
			if (apply_cursor_key(command, term, LEFT_ARROW) == -1)
				return (-1);
	}
	else if ((command->cursor < command->length) && (key == END))
	{
		len = command->temp.length;
		while (len--)
			if (apply_cursor_key(command, term, RIGHT_ARROW) == -1)
				return (-1);
	}
	return (1);
}

int		apply_cursor_key(t_command *command, t_term *term, int key)
{
	char		ch;

	init_term_size(command, term);
	if ((command->cursor > 0) && key == LEFT_ARROW)
	{
		delete_string(&command->line, command->line.length - 1, &ch);
		if (!add_string(&command->temp, 0, ch))
			return (-1);
		command->cursor--;
		write(1, &key, sizeof(key));
	}
	else if ((command->cursor < command->length) && key == RIGHT_ARROW)
	{
		delete_string(&command->temp, 0, &ch);
		if (!add_string(&command->line, command->line.length, ch))
			return (-1);
		command->cursor++;
		if (term->pos.cur_col == term->pos.col - 1)
			tputs(tgoto(term->cp.cm, 0, ++term->pos.cur_row), 1, tputs_wrapper);
		else
			write(1, &key, sizeof(key));
	}
	return (1);
}

int		apply_history_key(t_command *command, t_term *term, int key)
{
	static char	*str;
	int			bell;
	int			len;

	len = command->temp.length;
	while (len--)
		if (apply_cursor_key(command, term, RIGHT_ARROW) == -1)
			return (-1);
	if (!save_command(command, &str))
		return (-1);
	len = command->line.length;
	while (len--)
		if (apply_delete_key(command, term) == -1)
			return (-1);
	tputs(term->cp.cd, 1, tputs_wrapper);
	bell = change_command(command, key);
	command->line.length = 0;
	command->temp.length = 0;
	command->length = 0;
	command->cursor = 0;
	if (!load_command(command, str, bell))
		return (-1);
	return (1);
}

int		apply_delete_key(t_command *command, t_term *term)
{
	char	dump;

	init_term_size(command, term);
	if (command->line.length <= 0)
		return (1);
	if (apply_cursor_key(command, term, LEFT_ARROW) == -1)
		return (-1);
	delete_string(&command->temp, 0, &dump);
	refresh_command(command, term);
	command->length--;
	return (1);
}

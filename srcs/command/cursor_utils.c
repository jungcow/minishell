/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungwkim <jungwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 20:10:02 by jungwkim          #+#    #+#             */
/*   Updated: 2021/04/26 20:17:11 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <termcap.h>
#include "command/command.h"

static int	init_flag(char *str, int index)
{
	if (ft_isalnum(str[index]))
		return (1);
	else
		return (0);
}

int			move_cursor_lineby(t_command *command, t_term *term, int key)
{
	int		len;

	init_term_size(command, term);
	len = term->pos.col;
	if (key == CTRL_UP)
	{
		while (len--)
			if (apply_cursor_key(command, term, LEFT_ARROW) == -1)
				return (-1);
	}
	else if (key == CTRL_DOWN)
	{
		while (len--)
			if (apply_cursor_key(command, term, RIGHT_ARROW) == -1)
				return (-1);
	}
	return (1);
}

int			move_cursor_wordby(t_command *command, t_term *term, int key)
{
	int		flag;

	flag = -1;
	if (key == CTRL_LEFT)
	{
		while (command->cursor > 0 && !(flag == 1 &&
			!ft_isalnum(command->line.content[command->line.length - 1])))
		{
			flag = init_flag(command->line.content, command->line.length - 1);
			if (apply_cursor_key(command, term, LEFT_ARROW) == -1)
				return (-1);
		}
	}
	else if (key == CTRL_RIGHT)
	{
		while ((command->cursor < command->length) && !(flag == 0 &&
			ft_isalnum(command->temp.content[1])))
		{
			flag = init_flag(command->temp.content, 1);
			if (apply_cursor_key(command, term, RIGHT_ARROW) == -1)
				return (-1);
		}
	}
	return (1);
}

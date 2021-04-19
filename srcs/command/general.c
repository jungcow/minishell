/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoh <seunghoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 16:10:56 by seunghoh          #+#    #+#             */
/*   Updated: 2021/04/19 12:50:49 by seunghoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <termcap.h>
#include "command/command.h"

int		apply_general_key(t_command *command, t_term *term, int key)
{
	(void)term;
	int	i;

	i = 0;
	if (key >= 32 &&
		key <= 127)
	{
		if (!add_string(&command->line, command->line.length, key))
			return (-1);
		command->length++;
		command->cursor++;
		write(1, &key, 1);
		if (command->temp.length != 0)
		{
			tputs(tgetstr("cd", NULL), 1, tputs_wrapper);
			write(1, command->temp.content, command->temp.length);
			while (i < command->temp.length)
			{
				key = LEFT_ARROW;
				write(1, &key, sizeof(key));
				++i;
			}
		}
	}
	return (1);
}

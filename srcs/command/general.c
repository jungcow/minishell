/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoh <seunghoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 16:10:56 by seunghoh          #+#    #+#             */
/*   Updated: 2021/04/20 23:19:13 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <termcap.h>
#include "command/command.h"

int		apply_general_key(t_command *command, t_term *term, int key)
{
	if (key >= 32 && key <= 127)
	{
		if (!add_string(&(*command->command_line)->line,
					(*command->command_line)->line.length, key))
			return (-1);
		(*command->command_line)->length++;
		(*command->command_line)->cursor++;
		write(1, &key, 1);
		refresh_command(command, term);
	}
	return (1);
}

int		apply_quote_key(t_command *command, int key)
{
	(void)command;
	key++;
	return (1);
}

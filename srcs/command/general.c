/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoh <seunghoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 16:10:56 by seunghoh          #+#    #+#             */
/*   Updated: 2021/04/18 01:39:28 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <termcap.h>
#include "command/command.h"

int		apply_general_key(t_command *command, t_term *term, int key)
{
	(void)term;
	if (key >= 32 &&
		key <= 127)
	{
		if (!add_string(&command->line, command->line.length, key))
			return (-1);
		command->length++;
		command->cursor++;
		write(1, &key, 1);
	}
	return (1);
}

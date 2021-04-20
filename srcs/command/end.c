/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoh <seunghoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 16:26:27 by seunghoh          #+#    #+#             */
/*   Updated: 2021/04/21 00:28:46 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "command/command.h"

static int	quote_on(t_command *command, t_term *term)
{
	char	ch;

	while (delete_string(&(*command->command_line)->temp, 0, &ch))
		add_string(&(*command->command_line)->line,
				(*command->command_line)->line.length, ch);
	if (apply_general_key(command, term, '\n') == -1)
		return (-1);
	(*command->command_line)->length = 0;
	(*command->command_line)->cursor = 0;
	write(1, ">", 1);
	return (1);
}

static int	quote_off(t_command *command)
{
	char	ch;

	while (delete_string(&(*command->command_line)->temp, 0, &ch))
		add_string(&(*command->command_line)->line,
				(*command->command_line)->line.length, ch);
	if (!add_history(command))
	{
		clear_historylist(command->head);
		return (-1);
	}
	return (0);
}

int			apply_end_key(t_command *command, t_term *term, int key)
{
	if (key == ENTER)
	{
		if (command->quote_status)
			return (quote_on(command, term));
		else
			return (quote_off(command));
	}
	return (1);
}

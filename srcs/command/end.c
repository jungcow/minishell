/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoh <seunghoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 16:26:27 by seunghoh          #+#    #+#             */
/*   Updated: 2021/04/27 22:26:55 by seunghoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "command/command.h"

static int	quote_on(t_command *command, t_term *term)
{
	char	ch;

	while (delete_string(&command->temp, 0, &ch))
		add_string(&command->line, command->line.length, ch);
	if (apply_general_key(command, term, '\n') == -1)
		return (-1);
	command->length = 0;
	command->cursor = 0;
	write(1, ">", 1);
	return (1);
}

static int	quote_off(t_command *command)
{
	char	ch;
	char	ret;

	write(1, "\n", 1);
	while (delete_string(&command->temp, 0, &ch))
		if (!add_string(&command->line, command->line.length, ch))
			return (-1);
	if (!add_string(&command->line, command->line.length, '\0'))
		return (-1);
	ret = add_history(command, command->line.content, command->line.length);
	if (ret == 0)
	{
		clear_history(command->history, command->history_fd);
		return (-1);
	}
	if (ret == 1)
		write_history(command->history, command->history_fd);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungwkim <jungwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 21:03:59 by jungwkim          #+#    #+#             */
/*   Updated: 2021/04/17 05:46:37 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command/command.h"
#include <termcap.h>

void	write_historyfile(t_command *command, char *num_str)
{
	write(command->history_fd, "  ", 2);
	write(command->history_fd, num_str, ft_strlen(num_str));
	write(command->history_fd, "  ", 2);
	write(command->history_fd, command->line.content, command->line.length);
	write(command->history_fd, "\n", 1);
}

void	show_history(t_command *command, char *str, int flag)
{
	tputs(tgetstr("ce", NULL), 1, tputs_wrapper);
	if (flag)
	{
		write(1, "\a", 1); //write bell sound
		if (flag == 2)
		{
			write(1, command->line.content, command->line.length);
			write(1, command->temp.content, command->temp.length);
		}
		else
			write(1, str, ft_strlen(str));
	}
	else
		write(1, str, ft_strlen(str));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungwkim <jungwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 21:03:59 by jungwkim          #+#    #+#             */
/*   Updated: 2021/04/17 17:37:10 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command/command.h"
#include <termcap.h>

int		write_historyfile(t_command *command, t_history *new)
{
	char	*num_str;

	num_str = ft_itoa(new->num);
	if (num_str == NULL)
		return (0);
	write(command->history_fd, "  ", 2);
	write(command->history_fd, num_str, ft_strlen(num_str));
	write(command->history_fd, "  ", 2);
	write(command->history_fd, command->line.content, command->line.length);
	write(command->history_fd, "\n", 1);
	free(num_str);
	return (1);
}

void	write_historyline(t_command *command, char *str, int flag)
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

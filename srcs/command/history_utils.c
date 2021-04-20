/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungwkim <jungwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 21:03:59 by jungwkim          #+#    #+#             */
/*   Updated: 2021/04/20 23:19:37 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command/command.h"
#include <termcap.h>

void		write_historyfd(t_history *new, int fd)
{
	write(fd, new->line.content, new->line.length);
	write(fd, new->temp.content, new->temp.length);
	if (fd > 2)
		write(fd, "\n", 1);
}

static void	get_command_lines(t_command *command, t_term *term,
					t_history *prev_history, int prev_flag)
{
	if (!prev_flag)
		term->pos.row = (command->present->line.length + ft_strlen(term->name))
						/ term->pos.col;
	else
		term->pos.row = (prev_history->line.length + ft_strlen(term->name))
						/ term->pos.col;
}

static void	save_prev(t_history *history, t_history **prev_history,
												int flag, int *prev_flag)
{
	if (flag == 2)
	{
		*prev_flag = 0;
		(void)prev_history;
	}
	else
	{
		*prev_flag = 1;
		*prev_history = history;
	}
}

void		write_historyline(t_command *command, t_term *term,
							t_history *history, int flag)
{
	static int			prev_flag;
	static t_history	*prev_history;

	init_term_size(command, term);
	get_command_lines(command, term, prev_history, prev_flag);
	term->pos.cur_row = term->pos.cur_row - term->pos.row;
	tputs(tgoto(term->cp.cm, ft_strlen(term->name), term->pos.cur_row),
														1, tputs_wrapper);
	tputs(term->cp.cd, 1, tputs_wrapper);
	if (flag)
	{
		write(1, "\a", 1); //write bell sound
		if (flag == 2)
			write_historyfd(command->present, 1);
		else
			write_historyfd(history, 1);
	}
	else
		write_historyfd(history, 1);
	save_prev(history, &prev_history, flag, &prev_flag);
}

void		clear_historylist(t_history **head)
{
	t_history	*temp;

	while (*head)
	{
		temp = *head;
		*head = (*head)->before;
		clear_history(&temp);
	}
	head = NULL;
}

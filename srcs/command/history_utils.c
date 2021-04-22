/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungwkim <jungwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 21:03:59 by jungwkim          #+#    #+#             */
/*   Updated: 2021/04/22 03:40:34 by jungwkim         ###   ########.fr       */
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
	int		command_line_len;
	int		name_len;
	init_term_size(command, term);
	name_len = ft_strlen(term->name);
	if (!prev_flag)
		command_line_len = command->present->line.length;
	else
		command_line_len = prev_history->line.length;
	term->pos.row = (command_line_len + name_len - 1) / term->pos.col;
//	if ((name_len) / term->pos.col >= 1)
//		term->pos.row -= (name_len) / term->pos.col; <- 이부분은 name_len이 한 줄이 넘어갈 때에 문제를 해결한 것
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
// name_len이 col이랑 같을 때 문제가 생김 <- 이부분 해결 요망
void		write_historyline(t_command *command, t_term *term,
							t_history *history, int flag)
{
	static int			prev_flag;
	static t_history	*prev_history;
//	int					name_col;

	get_command_lines(command, term, prev_history, prev_flag);
	term->pos.cur_row = term->pos.cur_row - term->pos.row;
//	if ((ft_strlen(term->name)) % term->pos.col == 0)
//	{
//		name_col = 0;
	//	term->pos.cur_row += 1;
//	}
//	else
//		name_col = ft_strlen(term->name);
	tputs(tgoto(term->cp.cm, ft_strlen(term->name) % term->pos.col, term->pos.cur_row), 1, tputs_wrapper);
	tputs(term->cp.cd, 1, tputs_wrapper);
	if (flag)
	{
		write(1, "\a", 1);
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

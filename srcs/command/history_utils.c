/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungwkim <jungwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 21:03:59 by jungwkim          #+#    #+#             */
/*   Updated: 2021/04/19 18:37:36 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command/command.h"
#include <termcap.h>

int			write_historyfile(t_command *command, t_history *new)
{
	char	*num_str;
	int		num;

	num_str = ft_itoa(new->num);
	if (num_str == NULL)
		return (0);
	num = 5 - ft_strlen(num_str);
	while (num--)
		write(command->history_fd, " ", 1);
	write(command->history_fd, num_str, ft_strlen(num_str));
	write(command->history_fd, "  ", 2);
	write(command->history_fd, new->str, ft_strlen(new->str));
	write(command->history_fd, "\n", 1);
	free(num_str);
	return (1);
}

static void	get_command_lines(t_command *command, t_term *term,
					char *prev_str, int prev_flag)
{
	init_term_size(command, term);
	if (!prev_flag)
		term->pos.row = (command->line.length + ft_strlen(term->name))
						/ term->pos.col;
	else
		term->pos.row = (ft_strlen(prev_str) + ft_strlen(term->name))
						/ term->pos.col;
}

static void	save_prev(char *str, char **prev_str, int flag, int *prev_flag)
{
	if (flag == 2)
	{
		*prev_flag = 0;
		(void)prev_str;
	}
	else
	{
		*prev_flag = 1;
		*prev_str = str;
	}
}

void		write_historyline(t_command *command, t_term *term,
							char *str, int flag)
{
	static int	prev_flag;
	static char *prev_str;

	get_command_lines(command, term, prev_str, prev_flag);
	get_cursor_pos(term);
	term->pos.cur_row = term->pos.cur_row - term->pos.row;
	tputs(tgoto(term->cap.cm, ft_strlen(term->name), term->pos.cur_row),
														1, tputs_wrapper);
	tputs(term->cap.cd, 1, tputs_wrapper);
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
	save_prev(str, &prev_str, flag, &prev_flag);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungwkim <jungwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 06:05:34 by jungwkim          #+#    #+#             */
/*   Updated: 2021/05/01 04:05:53 by seunghoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMINAL_H
# define TERMINAL_H

# include <termios.h>
# include <curses.h>

typedef struct		s_pos
{
	int				col;
	int				row;
	int				cur_col;
	int				cur_row;
}					t_pos;

typedef struct		s_cp
{
	char			*cm;
	char			*im;
	char			*ei;
	char			*cd;
	char			*ce;
	char			*dc;
}					t_cp;

typedef struct		s_term
{
	const char		*name;
	struct termios	save_term;
	t_cp			cp;
	t_pos			pos;
}					t_term;

int					tputs_wrapper(int tc);
int					get_cursor_pos(t_term *term);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungwkim <jungwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 16:59:29 by jungwkim          #+#    #+#             */
/*   Updated: 2021/05/07 18:54:02 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termcap.h>
#include <curses.h>
#include <termios.h>
#include <stdlib.h>
#include <terminal.h>
#include <unistd.h>

int		tputs_wrapper(int tc)
{
	write(1, &tc, 1);
	return (0);
}

int		init_termcap(t_cp *capability)
{
	char	*termtype;

	termtype = getenv("TERM");
	if (termtype == NULL)
		return (0);
	tgetent(NULL, termtype);
	capability->cm = tgetstr("cm", NULL);
	capability->im = tgetstr("im", NULL);
	capability->ei = tgetstr("ei", NULL);
	capability->cd = tgetstr("cd", NULL);
	capability->ce = tgetstr("ce", NULL);
	capability->dc = tgetstr("dc", NULL);
	return (1);
}

void	init_terminal(t_term *term)
{
	tcgetattr(STDIN_FILENO, &term->save_term);
	term->new_term = term->save_term;
	term->new_term.c_lflag &= ~ICANON;
	term->new_term.c_lflag &= ~ECHO;
	term->new_term.c_cc[VMIN] = 1;
	term->new_term.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &term->new_term);
}

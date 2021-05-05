/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoh <seunghoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 22:18:05 by seunghoh          #+#    #+#             */
/*   Updated: 2021/05/05 20:28:54 by seunghoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <termios.h>
#include <termcap.h>
#include <curses.h>
#include <stdlib.h>
#include <signal.h>
#include "libft.h"
#include "terminal.h"
#include "command/command.h"
#include "execute/execute.h"
#include "builtin.h"

t_command	g_command;

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

void	init_signal(void)
{
	signal(SIGINT, (void *)sigint_handler);
	signal(SIGQUIT, (void*)sigquit_handler);
}

int		init_minishell(t_term *term, t_command *command)
{
	if (!init_termcap(&term->cp) ||
		!init_history(command))
		return (0);
	init_signal();
	tcgetattr(STDIN_FILENO, &term->save_term);
	term->new_term = term->save_term;
	term->new_term.c_lflag &= ~ICANON;
	term->new_term.c_lflag &= ~ECHO;
	term->new_term.c_cc[VMIN] = 1;
	term->new_term.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &term->new_term);
	return (1);
}

void	run_minishell(void)
{
	t_term		term;

	term.name = "seung-jung$>";
	ft_pwd();
	if (!init_minishell(&term, &g_command))
		return ;
	while (42)
	{
		tcsetattr(STDIN_FILENO, TCSANOW, &term.new_term);
		if (!init_command(&g_command))
			break ;
		if (!read_command(&g_command, &term))
			break ;
		tcsetattr(STDIN_FILENO, TCSANOW, &term.save_term);
		if (!validate_command(&g_command))
			break ;
		if (run_command(&g_command) == -1)
			break ;
		clear_command(&g_command);
	}
	clear_command(&g_command);
	clear_history(g_command.history, g_command.history_fd);
	tcsetattr(STDIN_FILENO, TCSANOW, &term.save_term);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoh <seunghoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 22:18:05 by seunghoh          #+#    #+#             */
/*   Updated: 2021/05/02 17:15:20 by seunghoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <termios.h>
#include <termcap.h>
#include <curses.h>
#include <stdlib.h>
#include "libft.h"
#include "terminal.h"
#include "command/command.h"
#include "execute/execute.h"

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

int		init_minishell(t_term *term, t_command *command)
{
	struct termios	new_term;

	if (!init_termcap(&term->cp) ||
		!init_history(command))
		return (0);
	tcgetattr(STDIN_FILENO, &term->save_term);
	new_term = term->save_term;
	new_term.c_lflag &= ~ICANON;
	new_term.c_lflag &= ~ECHO;
	new_term.c_cc[VMIN] = 1;
	new_term.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &new_term);
	return (1);
}

void	run_minishell(void)
{
	t_term		term;
	t_command	command;

	term.name = "seung-jung$>";
	if (!init_minishell(&term, &command))
		return ;
	while (42)
	{
		if (!init_command(&command))
			break ;
		if (!read_command(&command, &term))
			break ;
		if (!validate_command(&command))
			break ;
		if (run_command(&command) == -1)
			break ;
		clear_command(&command);
	}
	clear_command(&command);
	clear_history(command.history, command.history_fd);
	tcsetattr(STDIN_FILENO, TCSANOW, &term.save_term);
}

int		main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	g_environ = env;
	run_minishell();
	return (0);
}

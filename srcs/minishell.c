/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoh <seunghoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 22:18:05 by seunghoh          #+#    #+#             */
/*   Updated: 2021/04/17 05:46:55 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <termios.h>
#include <termcap.h>
#include <curses.h>
#include "libft.h"
#include "command/command.h"

int		tputs_wrapper(int tc)
{
	write(1, &tc, 1);
	return (0);
}

void	init_minishell()
{
	struct termios	term;
	char			*im;
	
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~ICANON;
    term.c_lflag &= ~ECHO;
    term.c_cc[VMIN] = 1;
    term.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
	tgetent(NULL, "xterm");
	im = tgetstr("im", NULL);
	tputs(im, 1, tputs_wrapper);
}

void	run_minishell()
{
	t_command	command;
	t_history	*head;
	
	init_minishell();
	// error
	if (!init_command(&command, &head))
		return ;
	read_command(&command);
	clear_command(&command);
	tputs(tgetstr("ei", NULL), 1, tputs_wrapper);
}

int		main()
{
	run_minishell();
	system("leaks minishell");
	return (0);
}

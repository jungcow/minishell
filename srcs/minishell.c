/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoh <seunghoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 22:18:05 by seunghoh          #+#    #+#             */
/*   Updated: 2021/05/11 11:18:50 by seunghoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "terminal.h"
#include "command/command.h"
#include "execute/execute.h"
#include "builtin.h"

t_command	g_command;

int		init_minishell(t_term *term, t_command *command)
{
	if (!init_termcap(&term->cp) ||
		!init_history(command))
		return (0);
	command->pwd = getcwd(NULL, 0);
	if (command->pwd == NULL)
		return (0);
	command->exit_status = 0;
	command->term = term;
	if (command->pwd == NULL)
		return (0);
	init_signal();
	init_terminal(term);
	return (1);
}

void	run_minishell(char **env)
{
	t_term		term;

	term.name = TERM_NAME;
	if (!init_minishell(&term, &g_command))
		return ;
	if (!init_environ(&g_command.environ, env))
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
	clear_environ(g_command.environ);
	tcsetattr(STDIN_FILENO, TCSANOW, &term.save_term);
}

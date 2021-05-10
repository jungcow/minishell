/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoh <seunghoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 16:39:04 by seunghoh          #+#    #+#             */
/*   Updated: 2021/05/10 18:48:20 by seunghoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <signal.h>
#include "libft.h"
#include "terminal.h"
#include "command/command.h"

extern t_command	g_command;

void	init_signal(void)
{
	signal(SIGINT, (void *)sigint_handler);
	signal(SIGQUIT, (void *)sigquit_handler);
}

void	sigint_handler(void)
{
	if (g_command.pid == 0)
	{
		while (g_command.cursor + 1 < g_command.length)
			if (apply_cursor_key(&g_command, g_command.term, RIGHT_ARROW) == -1)
				exit(1);
		clear_command(&g_command);
		if (!init_command(&g_command))
			exit(1);
		write(1, "\n", 1);
		write(1, TERM_NAME, ft_strlen(TERM_NAME));
		g_command.exit_status = 1;
	}
}

void	sigquit_handler(void)
{
}

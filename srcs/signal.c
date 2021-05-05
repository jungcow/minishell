/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoh <seunghoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 16:39:04 by seunghoh          #+#    #+#             */
/*   Updated: 2021/05/05 21:29:45 by seunghoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "terminal.h"
#include "command/command.h"

extern t_command	g_command;

void	sigint_handler(void)
{
	clear_command(&g_command);
	if (!init_command(&g_command))
		exit(1);
	write(1, "\n", 1);
	write(1, TERM_NAME, ft_strlen(TERM_NAME)); 
	g_command.exit_status = 1;
}

void	sigquit_handler(void)
{
}

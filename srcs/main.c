/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoh <seunghoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 16:22:02 by seunghoh          #+#    #+#             */
/*   Updated: 2021/05/07 11:58:05 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "terminal.h"
#include "command/command.h"

extern t_command	g_command;

int		main(int argc, char **argv, char **env)
{

	(void)argc;
	(void)argv;
	// should fix
//	g_command.env = env;
	print_ascii_art();
	run_minishell(env);
	// return what if error
	return (0);
}

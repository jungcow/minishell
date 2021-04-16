/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungwkim <jungwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 16:59:32 by jungwkim          #+#    #+#             */
/*   Updated: 2021/04/16 17:39:51 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command/terminal.h"
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

int		puts_t(int cp)
{
	write(1, &cp, 1);
	return (0);
}
#include <stdio.h>
void	init_capability(t_cap *cap)
{
	cap->termtype = getenv("TERM");
	tgetent(NULL, cap->termtype);
	printf("%s\n", cap->termtype);
	cap->cm = tgetstr("cm", NULL);
	cap->dc = tgetstr("dc", NULL);
	cap->im = tgetstr("im", NULL);
	cap->ei = tgetstr("ei", NULL);
	cap->name = "seungwkim$ ";
}

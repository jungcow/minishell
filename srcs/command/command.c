/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoh <seunghoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 21:55:18 by seunghoh          #+#    #+#             */
/*   Updated: 2021/04/15 21:58:06 by seunghoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include "libft.h"
#include "command/command.h"

# define LEFT_ARROW 4479771
# define RIGHT_ARROW 4414235

bool	init_command(t_command *command)
{
	bool	flag;

	command->keywords = NULL;
	command->keywords_size = 0;
	command->cursor = 0;
	flag = true;
	flag = flag && init_string(&command->line);
	flag = flag && init_string(&command->temp);
	if (flag == false)
		clear_command(command);
	return (flag);
}

int		read_command(t_command *command)
{
	char	ch;
	int		a;
	(void) command;

	while(1)
	{
		read(0, &ch, 1);
		if (ch == 27)
		{
			read(0, &ch, 1);
			read(0, &ch, 1);
			a = LEFT_ARROW;
			write(1, &a, 3);
		}
		else
		{
			write(1, &ch, 1);
		}
	}
	return (1);
}

void	clear_command(t_command *command)
{
	int		i;

	i = 0;
	if (command->keywords != NULL)
	{
		while (i < command->keywords_size)
			free(command->keywords[i++]);
		free(command->keywords);
	}
	command->keywords = NULL;
	command->keywords_size = 0;
	command->cursor = 0;
	clear_string(&command->line);
	clear_string(&command->temp);
}

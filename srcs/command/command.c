/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoh <seunghoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 21:55:18 by seunghoh          #+#    #+#             */
/*   Updated: 2021/04/16 17:44:16 by seunghoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdbool.h>
#include "libft.h"
#include "command/command.h"

bool	init_command(t_command *command)
{
	bool	flag;

	command->keywords = NULL;
	command->keywords_size = 0;
	command->cursor = 0;
	command->length = 0;
	flag = true;
	flag = flag && init_string(&command->line);
	flag = flag && init_string(&command->temp);
	if (flag == false)
		clear_command(command);
	return (flag);
}

int		read_command(t_command *command)
{
	int		key;
	int		flag;
	(void) command;

	while(42)
	{
		key = 0;
		flag = read(0, &key, sizeof(key));

		if (flag == -1)
			return (0);
		flag = switch_command(command, key);
		if (flag == -1)
			return (0);
		else if (flag == 0)
			break ;
	}
	return (1);
}

int		switch_command(t_command *command, int key)
{
	int		flag;

	if (key == LEFT_ARROW ||
		key == RIGHT_ARROW)
		flag = apply_cursor_key(command, key);
	else if (key == BACK_SPACE)
		flag = apply_delete_key(command, key);
	else if (key == UP_ARROW ||
			key == DOWN_ARROW)
		// apply history
		flag = 1;
	else if (key == QUOTE ||
			key == DOUBLE_QUOTE)
		flag = 1;
		// apply quate key
	else if (key == CTRL_D ||
			key == ENTER)
		flag = apply_end_key(command, key);
	else
		flag = apply_general_key(command, key);
	return (flag);
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
	command->length = 0;
	clear_string(&command->line);
	clear_string(&command->temp);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoh <seunghoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 21:55:18 by seunghoh          #+#    #+#             */
/*   Updated: 2021/04/19 16:15:11 by seunghoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <termcap.h>
#include <fcntl.h>
#include "command/command.h"

bool	init_command(t_command *command, t_history **head)
{
	bool		flag;

	command->keywords = NULL;
	command->keywords_size = 0;
	command->cursor = 0;
	command->length = 0;
	flag = true;
	flag = flag && init_string(&command->line);
	flag = flag && init_string(&command->temp);
	flag = flag && parse_history(&command->history_fd, head);
	if (flag == false)
		clear_command(command);
	command->head = head;
	return (flag);
}

int		read_command(t_command *command, t_term *term)
{
	int		key;
	int		flag;

	write(1, term->name, ft_strlen(term->name));
	init_term_size(command, term);
	while(42)
	{
		key = 0;
		flag = read(0, &key, sizeof(key));
		if (flag == -1)
			return (0);
		flag = switch_command(command, term, key);
		if (flag == -1)
			return (0);
		else if (flag == 0)
			break ;
	}
	return (1);
}

int		switch_command(t_command *command, t_term *term, int key)
{
	int		flag;

	if (key == LEFT_ARROW ||
		key == RIGHT_ARROW)
		flag = apply_cursor_key(command, term, key);
	else if (key == BACK_SPACE)
		flag = apply_delete_key(command, term);
	else if (key == UP_ARROW ||
			key == DOWN_ARROW)
		flag = apply_history_key(command, term, key);
	else if (key == QUOTE ||
			key == DOUBLE_QUOTE)
		flag = apply_quote_key(command,key);
	else if (key == CTRL_D ||
			key == ENTER)
		flag = apply_end_key(command, key);
	else
		flag = apply_general_key(command, term, key);
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
	close(command->history_fd);
	clear_string(&command->line);
	clear_string(&command->temp);
	clear_history(command->head);
}

int		save_command(t_command *command)
{
	t_history	*ptr;
	int			fd;
	int			index;

	fd = open("./.minish_history", O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd < 0)
		return (0);
	command->history_fd = fd;
	ptr = *(command->head);
	while (ptr->before)
		ptr = ptr->before;
	index = 1;
	while (ptr)
	{
		ptr->num = index++;
		if (!write_historyfile(command, ptr))
			return (0);
		ptr = ptr->next;
	}
	return (1);
}

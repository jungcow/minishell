/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungwkim <jungwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 14:42:02 by jungwkim          #+#    #+#             */
/*   Updated: 2021/04/24 14:50:36 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command/command.h"
#include <fcntl.h>
#include <unistd.h>

int		init_history(t_command *command)
{
	int			fd;
	int			ret;
	char		*line;

	line = NULL;
	command->history = NULL;
	command->ptr = NULL;
	fd = open("./.minish_history", O_CREAT | O_RDWR, 0644);
	if (fd < 0)
		return (0);
	command->history_fd = fd;
	while ((ret = get_next_line(fd, &line)) >= 0)
	{
		if (ret == -1 || !add_history(command, line, ft_strlen(line)))
		{
			clear_history(command->history, command->history_fd);
			return (0);
		}
		free(line);
		if (ret == 0)
			break ;
	}
	return (1);
}

int		add_history(t_command *command, char *line, size_t len)
{
	t_history	*new;

	if (!(*line))
		return (1);
	new = (t_history *)malloc(sizeof(t_history));
	if (new == NULL)
		return (0);
	new->str = ft_strndup(line, len);
	if (new->str == NULL)
		return (0);
	new->before = NULL;
	new->next = NULL;
	if (command->history)
	{
		command->history->next = new;
		new->before = command->history;
	}
	command->history = new;
	command->ptr = command->history;
	return (1);
}

void	write_historyfile(t_history *history, int fd)
{
	write(fd, history->str, ft_strlen(history->str));
	write(fd, "\0", 1);
}

void	clear_history(t_history *history, int fd)
{
	t_history	*temp;

	while (history)
	{
		temp = history;
		history = history->before;
		free(temp->str);
		temp->next = NULL;
		temp->before = NULL;
		free(temp);
	}
	close(fd);
}

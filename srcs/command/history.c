/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungwkim <jungwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 14:42:02 by jungwkim          #+#    #+#             */
/*   Updated: 2021/04/24 13:51:50 by jungwkim         ###   ########.fr       */
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
	command->history->next = NULL;
	command->history->before = NULL;
	command->history->str = NULL;
	fd = open("./.minish_history", O_CREAT | O_RDWR, 0644);
	if (fd < 0)
		return (0);
	while ((ret = get_next_line(fd, &line)) >= 0)
	{
		if (ret == -1 || !add_history(command, line, ft_strlen(line)))
		{
			clear_history(command->history);
			return (0);
		}
		free(line);
		if (ret == 0)
			break ;
	}
	close(fd);
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
	if (command->history->before)
	{
		command->history->before->next = new;
		new->before = command->history->before;
	}
	command->history->before = new;
	command->ptr = command->history->before;
	return (1);
}

void	write_historyfile(t_history *history)
{
	int			fd;
	t_history	*ptr;

	ptr = history->before;
	fd = open("./.minish_history", O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd < 0)
		return ;
	while (ptr->before)
		ptr = ptr->before;
	while (ptr)
	{
		printf("write: %s\n", ptr->str);
		write(fd, ptr->str, ft_strlen(ptr->str));
		write(fd, "\0", 1);
		ptr = ptr->next;
	}
	close(fd);
	return ;
}

void	clear_history(t_history *history)
{
	t_history	*temp;

	while (history->before)
	{
		temp = history->before;
		history->before = history->before->before;
		free(temp->str);
		temp->next = NULL;
		temp->before = NULL;
		free(temp);
	}
}

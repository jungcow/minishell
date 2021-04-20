/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungwkim <jungwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 18:12:13 by jungwkim          #+#    #+#             */
/*   Updated: 2021/04/21 00:29:24 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command/command.h"
#include <fcntl.h>
#include <unistd.h>

void	get_history(t_history **ptr, int *bottom, int *flag, int key)
{
	if (key == UP_ARROW)
	{
		if (!(*bottom))
			*bottom += 1;
		else if ((*ptr)->before && *bottom)
			(*ptr) = (*ptr)->before;
		else
			*flag = 1;
	}
	else if (key == DOWN_ARROW)
	{
		if ((*ptr)->next)
			(*ptr) = (*ptr)->next;
		else
		{
			if (*bottom)
				*bottom -= 1;
			*flag = 2;
		}
	}
}

int		init_history(t_history **head, t_history **new, char *line)
{
	if (!line | !(*line))
		return (1);
	*new = (t_history *)malloc(sizeof(t_history));
	if (*new == NULL)
		return (0);
	init_string(&(*new)->line);
	init_string(&(*new)->temp);
	ft_strncpy((*new)->line.content, line, ft_strlen(line));
	(*new)->line.length = ft_strlen(line);
	(*new)->length = ft_strlen(line);
	(*new)->cursor = ft_strlen(line);
	(*new)->before = NULL;
	(*new)->next = NULL;
	if (*head != NULL)
	{
		(*new)->before = *head;
		(*head)->next = *new;
	}
	*head = *new;
	return (1);
}

void	clear_history(t_history **contents)
{
	clear_string(&(*contents)->line);
	clear_string(&(*contents)->temp);
	(*contents)->length = 0;
	(*contents)->cursor = 0;
	(*contents)->next = NULL;
	(*contents)->before = NULL;
	free(*contents);
}

int		parse_history(int *history_fd, t_history **head)
{
	int			fd;
	char		*line;
	int			ret;
	t_history	*new;

	line = NULL;
	*head = NULL;
	fd = open("./.minish_history", O_CREAT | O_RDWR, 0644);
	if (fd < 0)
		return (0);
	*history_fd = fd;
	while ((ret = get_next_line(fd, &line)) >= 0)
	{
		if (!init_history(head, &new, line))
		{
			clear_historylist(head);
			return (0);
		}
		free(line);
		if (ret == 0)
			break ;
	}
	return (1);
}

int		add_history(t_command *command)
{
	t_history	*new;

	if (*(command->head) != NULL && (!((*command->command_line)->line.content)
				|| *(*command->command_line)->line.content == '\0'))
		return (1);
	new = (t_history *)malloc(sizeof(t_history));
	if (new == NULL)
		return (0);
	if (!init_string(&new->line) || !init_string(&new->temp))
		return (0);
	ft_strncpy(new->line.content, (*command->command_line)->line.content,
								(*command->command_line)->line.length);
	new->line.length = (*command->command_line)->line.length;
	new->length = (*command->command_line)->line.length;
	new->cursor = (*command->command_line)->line.length;
	new->next = NULL;
	new->before = NULL;
	if (*(command->head) != NULL)
	{
		new->before = *(command->head);
		(*(command->head))->next = new;
	}
	*(command->head) = new;
	write_historyfd(new, command->history_fd);
	return (1);
}

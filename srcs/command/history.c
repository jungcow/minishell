/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungwkim <jungwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 18:12:13 by jungwkim          #+#    #+#             */
/*   Updated: 2021/04/17 17:12:28 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command/command.h"
#include <fcntl.h>
#include <unistd.h>
// cursor.c 에서 호출함
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
	if (!line || !(*line))
		return (1);
	*new = (t_history *)malloc(sizeof(t_history));
	if (*new == NULL)
		return (0);
	(*new)->num = ft_atoi(line); //history numbers
	while (ft_isspace(*line))
		line++;
	while (ft_isdigit(*line))
		line++;
	line += 2; // jump two spaces
	(*new)->str = ft_strdup(line); //history contents
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

void	clear_history(t_history **head)
{
	t_history	*temp;

	(*head)->next = NULL;
	while (*head)
	{
		temp = *head;
		(*head) = (*head)->before;
		free(temp->str);
		free(temp);
	}
	head = NULL;
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
			clear_history(head);
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

	if (*(command->head) != NULL && ((*(command->head))->str == NULL
				|| *(*(command->head))->str == '\0'))
		return (1); // 아무 입력 없이 enter 쳤을 시 저장 안함.
	new = (t_history *)malloc(sizeof(t_history));
	if (new == NULL)
		return (0);
	new->str = ft_strndup(command->line.content, command->line.length);
	if (new->str == NULL)
		return (0);
	new->num = 1;
	new->next = NULL;
	new->before = NULL;
	if (*(command->head) != NULL)
	{
		new->num = (*(command->head))->num + 1;
		new->before = *(command->head);
		(*(command->head))->next = new;
	}
	*(command->head) = new;
	if (!write_historyfile(command, new))
		return (0);
	return (1);
}

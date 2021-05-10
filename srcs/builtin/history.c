/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungwkim <jungwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 14:18:09 by jungwkim          #+#    #+#             */
/*   Updated: 2021/05/10 14:55:53 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command/command.h"
#include "builtin.h"
#include "libft.h"

extern t_command	g_command;

int		ft_history(void)
{
	t_history	*history;
	char		*num_str;
	int			i;

	history = g_command.history;
	while (history->before)
		history = history->before;
	i = 1;
	while (history)
	{
		num_str = ft_itoa(i);
		if (num_str == NULL)
			return (-1);
		write(1, "     ", (5 - ft_strlen(num_str)));
		write(1, num_str, ft_strlen(num_str));
		write(1, "  ", 2);
		write(1, history->str, ft_strlen(history->str));
		write(1, "\n", 1);
		i++;
		history = history->next;
		free(num_str);
	}
	return (1);
}

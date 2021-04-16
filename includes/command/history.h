/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungwkim <jungwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 18:39:16 by jungwkim          #+#    #+#             */
/*   Updated: 2021/04/17 02:57:18 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

typedef struct			s_history
{
	char				*str;
	int					num;
	int					fd;
	struct s_history	*next;
	struct s_history	*before;
}						t_history;

int		init_history(t_history **head, t_history **new, char *line);
int		parse_history(int *history_fd, t_history **head);
void	clear_history(t_history **head);

#endif

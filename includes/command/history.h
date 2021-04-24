/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungwkim <jungwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 18:39:16 by jungwkim          #+#    #+#             */
/*   Updated: 2021/04/24 16:29:13 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

# include "libft.h"

typedef struct			s_history
{
	char				*str;
	struct s_history	*next;
	struct s_history	*before;
}						t_history;

void					write_history(t_history *history, int fd);
void					clear_history(t_history *history, int fd);
//int						parse_history(int *history_fd, t_history **head);
//void					clear_historylist(t_history **head);
//void					write_historyfd(t_history *new, int fd);
#endif

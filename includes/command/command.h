/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoh <seunghoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 21:54:40 by seunghoh          #+#    #+#             */
/*   Updated: 2021/04/22 01:26:46 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# define BACK_SPACE 127
# define LEFT_ARROW 4479771
# define RIGHT_ARROW 4414235
# define UP_ARROW 4283163
# define DOWN_ARROW 4348699
# define QUOTE 39
# define DOUBLE_QUOTE 34
# define ENTER 10
# define CTRL_D 4

# include <stdbool.h>
# include "libft.h"
# include "terminal.h"
# include "command/history.h"

typedef struct		s_command
{
	t_history		**head;
	t_history		*present;
	t_history		**command_line;
	int				history_fd;
	char			**keywords;
	int				keywords_size;
	bool			quote_status;
}					t_command;

bool				init_command(t_command *command, t_history **head);
int					read_command(t_command *command, t_term *term);
int					switch_command(t_command *command, t_term *term, int key);
void				clear_command(t_command *command);
int					save_command(t_command *command);
void				refresh_command(t_command *command, t_term *term);
int					apply_delete_key(t_command *command, t_term *term);
int					apply_cursor_key(t_command *command, t_term *term, int key);
int					apply_quote_key(t_command *command, t_term *term, int key);
int					apply_end_key(t_command *command, t_term *term, int key);
int					apply_general_key(t_command *command, t_term *term,
																	int key);
int					apply_history_key(t_command *command, t_term *term,
																	int key);
int					add_history(t_command *command);
void				write_historyfd(t_history *new, int fd);
void				write_historyline(t_command *command, t_term *term,
												t_history *history, int flag);
void				init_term_size(t_command *command, t_term *term);
int					get_history(t_command *command, t_history **ptr,
							int *bottom, int key);

#endif

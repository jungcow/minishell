/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoh <seunghoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 21:54:40 by seunghoh          #+#    #+#             */
/*   Updated: 2021/04/26 02:15:30 by jungwkim         ###   ########.fr       */
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
# define HOME 4741915
# define END 4610843
//# define CTRL_LEFT 1146821403
//# define CTRL_RIGHT 1130044187

# include <stdbool.h>
# include "libft.h"
# include "terminal.h"
# include "command/history.h"

typedef struct		s_command
{
	t_history		*history;
	int				history_fd;
	t_history		*ptr;
	t_string		line;
	t_string		temp;
	int				cursor;
	int				length;
	char			**keywords;
	int				keywords_size;
	bool			quote_status;
	bool			command_status;
}					t_command;

/*
**	control_command
*/
bool				init_command(t_command *command);
int					read_command(t_command *command, t_term *term);
int					switch_command(t_command *command, t_term *term, int key);
void				clear_command(t_command *command);

/*
**	command_utils
*/
void				refresh_command(t_command *command, t_term *term);
int					save_command(t_command *command, char **str);
int					change_command(t_command *command, int key);
int					load_command(t_command *command, char *str,
													int bell);
/*
**	control_key
*/
int					apply_delete_key(t_command *command, t_term *term);
int					apply_cursor_key(t_command *command, t_term *term, int key);
int					apply_multicursor_key(t_command *command, t_term *term, int key);
int					apply_quote_key(t_command *command, t_term *term, int key);
int					apply_end_key(t_command *command, t_term *term, int key);
int					apply_general_key(t_command *command, t_term *term,
																	int key);
int					apply_history_key(t_command *command, t_term *term,
																	int key);
/*
**	control_history
*/
int					init_history(t_command *command);
int					add_history(t_command *command, char *line, size_t len);

/*
**	control_term
*/
void				init_term_size(t_command *command, t_term *term);

#endif

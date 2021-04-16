/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoh <seunghoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 21:54:40 by seunghoh          #+#    #+#             */
/*   Updated: 2021/04/16 16:30:51 by seunghoh         ###   ########.fr       */
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

# include "libft.h"

typedef struct		s_command
{
	char			**keywords;
	int				keywords_size;
	t_string		line;
	t_string		temp;
	int				cursor;
	int				length;
}					t_command;

bool			    init_command(t_command *command);
int					read_command(t_command *command);
int					switch_command(t_command *command, int key);
void				clear_command(t_command *command);
int					apply_cursor_key(t_command *command, int key);
int					apply_history_key(t_command *command, int key);
int					apply_quote_key(t_command *command, int key);
int					apply_general_key(t_command *command, int key);
int					apply_end_key(t_command *command, int key);

#endif

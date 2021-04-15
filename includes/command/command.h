/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoh <seunghoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 21:54:40 by seunghoh          #+#    #+#             */
/*   Updated: 2021/04/15 21:32:04 by seunghoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include "libft.h"

typedef struct		s_command
{
	char			**keywords;
	int				keywords_size;
	t_string		line;
	t_string		temp;
	int				cursor;
}					t_command;

bool			    init_command(t_command *command);
int					read_command(t_command *command);
void				clear_command(t_command *command);
#endif

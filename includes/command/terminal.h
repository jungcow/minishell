/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungwkim <jungwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 06:05:34 by jungwkim          #+#    #+#             */
/*   Updated: 2021/04/17 06:09:25 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMINAL_H
# define TERMINAL_H

typedef struct		s_pos
{
	int				col;
	int				row;
}					t_pos;

typedef struct		s_cap
{
	char			*cm; //move curser
	char			*im; //turn on insert mode
	char			*ei; //turn off insert mode (actually, it is switch)
	char			*ce; // delete all characters before cursors
	char			*dc; // delete one characters at cursors
	t_pos			pos;
}					t_cap;

#endif

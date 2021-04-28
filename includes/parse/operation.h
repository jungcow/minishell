/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoh <seunghoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 18:20:57 by seunghoh          #+#    #+#             */
/*   Updated: 2021/04/28 19:07:07 by seunghoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERATION_H
# define OPERATION_H

# include "libft.h"

typedef struct	s_redirect
{
	int			from;
	t_string	to;
}				t_redirect;

typedef struct	s_operation
{
	t_string	name;
	t_redirect	*redirects;
	int			len_redirects;
	t_string	*argv;
	int			argc;
}				t_operation;

bool			init_operation(t_operation *operation);
void			clear_operation(t_operation *operation);

#endif

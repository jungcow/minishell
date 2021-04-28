/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoh <seunghoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 18:20:57 by seunghoh          #+#    #+#             */
/*   Updated: 2021/04/28 23:22:38 by seunghoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERATION_H
# define OPERATION_H

# include "libft.h"

typedef struct	s_redirect
{
	int			from;
	char		*to;
}				t_redirect;

typedef struct	s_operation
{
	int			argc;
	char		**argv;
	t_redirect	*redirects;
	int			len_redirects;
}				t_operation;

void			init_operation(t_operation *operation);
void			clear_operation(t_operation *operation);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoh <seunghoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 18:20:57 by seunghoh          #+#    #+#             */
/*   Updated: 2021/04/30 22:06:59 by seunghoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERATION_H
# define OPERATION_H

# include <stdbool.h>
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
bool			parse_operations(t_operation *operation, char **tokens);
void			clear_operation(t_operation *operation);

#endif

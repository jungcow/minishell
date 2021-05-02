/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoh <seunghoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 18:20:57 by seunghoh          #+#    #+#             */
/*   Updated: 2021/05/01 17:27:25 by seunghoh         ###   ########.fr       */
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
bool			create_redirection(t_operation *operation, int count);
int				count_redirection(char *token);
void			parse_redirection(t_redirect *redirect, char *token);
#endif

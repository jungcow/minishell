/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoh <seunghoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 16:25:50 by seunghoh          #+#    #+#             */
/*   Updated: 2021/04/28 14:19:42 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPELINE_H
# define PIPELINE_H

# include <stdbool.h>
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

typedef	struct	s_pipeline
{
	t_operation	*operations;
	int			length;
}				t_pipeline;

void			init_pipeline(t_pipeline *pipeline);
void			clear_pipeline(t_pipeline *pipeline);
bool			init_operation(t_operation *operation);
void			clear_operation(t_operation *operation);

int				parse_pipeline(char *token);
#endif

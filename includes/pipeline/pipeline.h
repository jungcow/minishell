/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoh <seunghoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 16:25:50 by seunghoh          #+#    #+#             */
/*   Updated: 2021/04/27 16:42:51 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H

typedef struct	s_redirect
{
	int			from;
	char		*to;
}				t_redirect

typedef struct	s_operation
{
	t_string	name;
	t_redirect	*redirects;
	t_string	*args;
}				t_operation;

typedef	struct	s_pipeline
{
	t_operation	*operations;
	int			length;
}				t_pipeline;

#endif

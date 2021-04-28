/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoh <seunghoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 18:10:59 by seunghoh          #+#    #+#             */
/*   Updated: 2021/04/28 22:11:55 by seunghoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPELINE_H
# define PIPELINE_H

# include "parse/operation.h"

typedef	struct	s_pipeline
{
	t_operation	*operations;
	int			length;
}				t_pipeline;


void			init_pipeline(t_pipeline *pipeline);
int				parse_pipeline(t_pipeline *pipeline, char **tokens);
void			clear_pipeline(t_pipeline *pipeline);

#endif

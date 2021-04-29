/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoh <seunghoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 17:13:40 by seunghoh          #+#    #+#             */
/*   Updated: 2021/04/29 02:23:22 by seunghoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse/pipeline.h"

void		init_pipeline(t_pipeline *pipeline)
{
	pipeline->operations = NULL;
	pipeline->length = 0;
}

int			parse_pipeline(t_pipeline *pipeline, char **tokens)
{
	if (!validate_pipeline(tokens))
		return (0);
	(void)pipeline;
	return (1);
}

void		clear_pipeline(t_pipeline *pipeline)
{
	int		i;

	i = 0;
	while (i < pipeline->length)
		clear_operation(&pipeline->operations[i++]);
	free(pipeline->operations);
	pipeline->operations = NULL;
	pipeline->length = 0;
}

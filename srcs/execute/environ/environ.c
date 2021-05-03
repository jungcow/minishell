/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungwkim <jungwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 03:46:24 by jungwkim          #+#    #+#             */
/*   Updated: 2021/05/03 21:17:02 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "execute/execute.h"

int		check_environ(t_pipeline *pipeline)
{
	t_envlist	*envlist;
	int			i;
	int			j;
	int			ret;

	i = -1;
	while (++i < pipeline->length)
	{
		j = -1;
		while (++j < pipeline->operations[i].argc)
		{
			envlist = NULL;
			ret = prepare_envlist(&envlist, pipeline->operations[i].argv[j]);
			if (ret >= 0)
				ret = replace_envlist(envlist);
			if (ret >= 0)
				ret = join_envlist(envlist, &pipeline->operations[i].argv[j]);
			clear_envlist(envlist);
			if (ret < 0)
				return (-1);
		}
	}
	return (1);
}

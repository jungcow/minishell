/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoh <seunghoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 19:33:04 by seunghoh          #+#    #+#             */
/*   Updated: 2021/04/27 19:55:48 by seunghoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "libft.h"
#include "pipeline/pipeline.h"

bool	init_operation(t_operation *operation)
{
	if (!init_string(&operation->name))
		return (false);
	operation->redirects = NULL;
	operation->len_redirects = 0;
	operation->argv = NULL;
	operation->argc = 0;
	return (true);
}

void	clear_operation(t_operation *operation)
{
	int		i;

	i = 0;
	while (i < operation->argc)
		clear_string(&operation->argv[i++]);
	free(operation->argv);
	operation->argv = NULL;
	i = 0;
	while (i < operation->len_redirects)
		clear_string(&operation->redirects[i++].to);
	free(operation->redirects);
	operation->redirects = NULL;
	clear_string(&operation->name);
	operation->len_redirects = 0;
	operation->argc = 0;
}

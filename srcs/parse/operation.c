/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoh <seunghoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 19:33:04 by seunghoh          #+#    #+#             */
/*   Updated: 2021/04/28 23:24:00 by seunghoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "libft.h"
#include "parse/operation.h"

void	init_operation(t_operation *operation)
{
	operation->argc = 0;
	operation->argv = NULL;
	operation->redirects = NULL;
	operation->len_redirects = 0;
}

void	clear_operation(t_operation *operation)
{
	int		i;

	i = 0;
	while (i < operation->argc)
		free(operation->argv[i++]);
	free(operation->argv);
	operation->argv = NULL;
	i = 0;
	while (i < operation->len_redirects)
		free(operation->redirects[i++].to);
	free(operation->redirects);
	operation->redirects = NULL;
	operation->len_redirects = 0;
	operation->argc = 0;
}

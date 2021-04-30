/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoh <seunghoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 19:33:04 by seunghoh          #+#    #+#             */
/*   Updated: 2021/04/30 22:06:29 by seunghoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdbool.h>
#include "libft.h"
#include "parse/operation.h"

// 매우 중요 >| 이거 그냥 리다이렉션이랑 똑같은표시

void	init_operation(t_operation *operation)
{
	operation->argc = 0;
	operation->argv = NULL;
	operation->redirects = NULL;
	operation->len_redirects = 0;
}

bool	parse_operations(t_operation *operations, char **tokens)
{
	(void)operations;
	while (*tokens)
	{
		printf("operation : [%s]\n", *tokens);
		tokens++;
	}
	return (true);
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

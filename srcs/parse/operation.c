/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoh <seunghoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 19:33:04 by seunghoh          #+#    #+#             */
/*   Updated: 2021/05/02 19:28:54 by seunghoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
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

bool	create_operation(t_operation *operation, int argc)
{
	operation->argv = (char **)malloc(sizeof(char *) * argc);
	if (operation->argv == NULL)
		return (false);
	operation->argc = argc;
	while (--argc >= 0)
		operation->argv[argc] = NULL;
	return (true);
}

bool	parse_operations(t_operation *operations, char **tokens)
{
	int		i;
	int		argc;
	int		len_redirects;
	bool	flag;

	i = 0;
	while (tokens[i] != NULL)
	{
		len_redirects = count_redirection(tokens[i]);
		flag = create_redirection(operations + i, len_redirects);
		if (!flag)
			break ;
		flag = parse_redirection(operations[i].redirects, tokens[i]);
		if (!flag)
			break ;
		(void)argc;
		/*argc = count_operation(tokens[i]);
		if (!create_operation(operations + i, argc))
		{
			clear_operation(operations);
			return (false);
		}*/
		i++;
	}
	return (flag);
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

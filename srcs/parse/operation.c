/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoh <seunghoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 19:33:04 by seunghoh          #+#    #+#             */
/*   Updated: 2021/05/08 20:05:50 by seunghoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	operation->argv = (char **)malloc(sizeof(char *) * (argc + 1));
	if (operation->argv == NULL)
		return (false);
	operation->argc = argc;
	operation->argv[argc] = NULL;
	while (--argc >= 0)
		operation->argv[argc] = NULL;
	return (true);
}

bool	parse_operations(t_operation *operations, char **tokens)
{
	int		i;
	bool	flag;

	i = 0;
	while (tokens[i] != NULL)
	{
		flag = create_redirection(operations + i, count_redirection(tokens[i]));
		if (!flag)
			break ;
		flag = parse_redirection(operations[i].redirects, tokens[i]);
		if (!flag)
			break ;
		flag = create_operation(operations + i, count_operation(tokens[i]));
		if (!flag)
			break ;
		flag = parse_operation(operations[i].argv, tokens[i]);
		if (!flag)
			break ;
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

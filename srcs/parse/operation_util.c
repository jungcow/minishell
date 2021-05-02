/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoh <seunghoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 19:39:15 by seunghoh          #+#    #+#             */
/*   Updated: 2021/05/02 22:03:54 by seunghoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "parse/parse_util.h"
#include "parse/operation.h"

int		count_operation2(char *token, int i)
{
	while (token[i] != '\0')
	{
		if (token[i] == ' ' || token[i] == '\n')
			break ;
		else if (token[i] == 34)
			i = skip_quote(token, ft_strlen(token), i);
		else if (token[i] == 39)
			i = skip_dquote(token, ft_strlen(token), i);
		i++;
	}
	return (i);
}

int		count_operation(char *token)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (token[i] != '\0')
	{
		if (token[i] == ' ' || token[i] == '\n')
			i = skip_space(token, ft_strlen(token), i);
		else
		{
			count++;
			i = count_operation2(token, i);
		}
		if (token[i] == '\0')
			break ;
		i++;
	}
	return (count);
}

int		move_operation(char **argv, char *token, int i)
{
	int		start;
	char	dump;

	start = i;
	while (token[i] != '\0')
	{
		if (token[i] == ' ' || token[i] == '\n')
			break ;
		else if (token[i] == 34)
			i = skip_quote(token, ft_strlen(token), i);
		else if (token[i] == 39)
			i = skip_dquote(token, ft_strlen(token), i);
		i++;
	}
	dump = token[i];
	token[i] = '\0';
	*argv = ft_strdup(token + start);
	if (*argv == NULL)
		return (-1);
	token[i] = dump;
	return (i);
}

bool	parse_operation(char **argv, char *token)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (token[i] != '\0')
	{
		if (token[i] == ' ' || token[i] == '\n')
			i = skip_space(token, ft_strlen(token), i);
		else
		{
			i = move_operation(argv + count, token, i);
			count++;
			if (i == -1)
				return (false);
		}
		if (token[i] == '\0')
			break ;
		i++;
	}
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoh <seunghoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 01:40:15 by seunghoh          #+#    #+#             */
/*   Updated: 2021/04/29 23:43:53 by seunghoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "parse/parse_util.h"
#include "error/error.h"

static bool	validate_token(char *token)
{
	int		i;
	bool	is_space;

	i = 0;
	is_space = true;
	while (token[i] != '\0')
	{
		if (token[i] == '|')
		{
			if (is_space)
			{
				write(2, TOKEN_ERR, ft_strlen(TOKEN_ERR));
				return (false);
			}
			token[i] = '\0';
			is_space = true;
		}
		else
			i = skip_pipeline(token, i, &is_space);
		i++;
	}
	return (true);
}


bool		validate_pipeline(char **tokens)
{
	int		i;

	i = 0;
	while (tokens[i] != NULL)
	{
		if (!validate_token(tokens[i]))
			return (false);
		i++;
	}
	return (true);
}

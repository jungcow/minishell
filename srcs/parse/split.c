/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoh <seunghoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 23:41:57 by seunghoh          #+#    #+#             */
/*   Updated: 2021/04/30 22:39:03 by seunghoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "parse/parse_util.h"

static int	count_token(char *line, int length)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (i < length)
	{
		if (line[i] == '\0')
			count++;
		i++;
	}
	return (count);
}

static bool	split_token(char **tokens, char *line, int length)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (i < length)
	{
		if (line[i] != '\0')
		{
			tokens[count++] = ft_strdup(line + i);
			if (tokens[count - 1] == NULL)
			{
				clear_tokens(tokens);
				return (false);
			}
			while (line[i] != '\0')
				i++;
		}
		i++;
	}
	return (true);
}

char		**split_tokens(char *line, int length)
{
	char		**tokens;
	int			count;

	count = count_token(line, length);
	tokens = (char **)malloc(sizeof(char *) * (count + 1));
	if (tokens == NULL)
		return (NULL);
	while (count >= 0)
		tokens[count--] = NULL;
	if (!split_token(tokens, line, length))
		return (NULL);
	return (tokens);
}

void		clear_tokens(char **tokens)
{
	int		i;
	
	i = 0;
	while (tokens[i] != NULL)
		free(tokens[i++]);
	free(tokens);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoh <seunghoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 23:41:57 by seunghoh          #+#    #+#             */
/*   Updated: 2021/04/28 00:46:49 by seunghoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "command/command.h"

static int	count_token(t_string *line)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (i < line->length)
	{
		if (line->content[i] == '\0')
			count++;
		i++;
	}
	return (count);
}

static bool	split_token(char **tokens, t_string *line)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (i < line->length)
	{
		if (line->content[i] != '\0')
		{
			tokens[count++] = ft_strdup(line->content + i);
			if (tokens[count - 1] == NULL)
			{
				clear_tokens(tokens);
				return (false);
			}
			while (line->content[i] != '\0')
				i++;
		}
		i++;
	}
	return (true);
}

char		**split_command(t_string *line)
{
	char		**tokens;
	int			count;

	count = count_token(line);
	tokens = (char **)malloc(sizeof(char *) * (count + 1));
	if (tokens == NULL)
		return (NULL);
	while (count >= 0)
		tokens[count--] = NULL;
	if (!split_token(tokens, line))
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

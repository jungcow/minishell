/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoh <seunghoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 17:13:40 by seunghoh          #+#    #+#             */
/*   Updated: 2021/05/01 03:47:03 by seunghoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "parse/pipeline.h"
#include "parse/parse_util.h"

void		init_pipeline(t_pipeline *pipeline)
{
	pipeline->operations = NULL;
	pipeline->length = 0;
}

void		refactor_pipeline(char *token)
{
	int		i;
	int		length;

	i = 0;
	length = ft_strlen(token);
	while (i < length)
	{
		if (token[i] == 34)
			i = skip_quote(token, length, i);
		else if (token[i] == 39)
			i = skip_dquote(token, length, i);
		else if (token[i] == '>' && token[i + 1] == '|')
			token[i + 1] = ' ';
		else if (token[i] == '|')
			token[i] = '\0';
		i++;
	}
}

bool		parse_pipeline(t_pipeline *pipeline, char **tokens)
{
	int		i;
	bool	flag;

	i = 0;
	while (tokens[i] != NULL)
		i++;
	pipeline->operations = (t_operation *)malloc(sizeof(t_operation) * i);
	if (pipeline->operations == NULL)
		return (false);
	i = 0;
	pipeline->length = i;
	while (i < pipeline->length)
	{
		init_operation(&pipeline->operations[i]);
		i++;
	}
	flag = parse_operations(pipeline->operations, tokens);
	return (flag);
}

bool		parse_pipelines(t_pipeline *pipelines, char **tokens)
{
	int		i;
	int		length;
	char	**pipe_tokens;

	i = 0;
	while (tokens[i] != NULL)
	{
		length = ft_strlen(tokens[i]) + 1;
		refactor_pipeline(tokens[i]);
		pipe_tokens = split_tokens(tokens[i], length);
		if (pipe_tokens == NULL)
			return (false);
		if (!parse_pipeline(pipelines + i, pipe_tokens))
		{
			clear_tokens(pipe_tokens);
			return (false);
		}
		clear_tokens(pipe_tokens);
		i++;
	}
	return (true);
}

void		clear_pipeline(t_pipeline *pipeline)
{
	int		i;

	i = 0;
	while (i < pipeline->length)
		clear_operation(&pipeline->operations[i++]);
	free(pipeline->operations);
	pipeline->operations = NULL;
	pipeline->length = 0;
}

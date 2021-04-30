/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoh <seunghoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 18:26:26 by seunghoh          #+#    #+#             */
/*   Updated: 2021/04/30 19:41:59 by seunghoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "libft.h"
#include "parse/parse_util.h"
#include "parse/operation.h"
#include "parse/instruction.h"
#include "error/error.h"

void		init_instruction(t_instruction *instruction)
{
	instruction->pipelines = NULL;
	instruction->length = 0;
}

bool		create_instruction(t_instruction *instruction, char **tokens)
{
	int		i;

	i = 0;
	while (tokens[i] != NULL)
		i++;
	instruction->pipelines = (t_pipeline *)malloc(sizeof(t_pipeline) * i);
	if (instruction->pipelines == NULL)
		return (false);
	instruction->length = i;
	i = 0;
	while (i < instruction->length)
	{
		init_pipeline(&instruction->pipelines[i]);
		i++;
	}
	return (true);
}

void		refactor_instruction(t_string *command)
{
	int		i;

	i = 0;
	while (i < command->length)
	{
		if (command->content[i] == 34)
			i = skip_quote(command->content, command->length, i);
		else if (command->content[i] == 39)
			i = skip_dquote(command->content, command->length, i);
		else if (command->content[i] == ';')
			command->content[i] = '\0';
		i++;
	}
	--i;
	while (--i >= 0)
		if (command->content[i] == ' ' ||
			command->content[i] == '\n')
			command->content[i] = '\0';
		else
			break ;
}

bool		parse_instruction(t_instruction *instruction, t_string *command)
{	
	char	**tokens;
	bool	flag;

	refactor_instruction(command);
	tokens = split_tokens(command->content, command->length);
	if (tokens == NULL)
		return (false);
	if (!create_instruction(instruction, tokens))
	{
		clear_tokens(tokens);
		return (false);
	}
	flag = parse_pipelines(instruction->pipelines, tokens);
	clear_tokens(tokens);
	return (flag);
}

void		clear_instruction(t_instruction *instruction)
{
	int		i;

	i = 0;
	while (i < instruction->length)
	{
		clear_pipeline(&instruction->pipelines[i]);
		i++;
	}
	free(instruction->pipelines);
}

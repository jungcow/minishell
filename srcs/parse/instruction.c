/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoh <seunghoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 18:26:26 by seunghoh          #+#    #+#             */
/*   Updated: 2021/04/29 23:42:39 by seunghoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
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

int			parse_instruction(t_instruction *instruction, t_string *command)
{	
	char	**tokens;
	int		flag;

	//if (!validate_instruction(command))
	//	return (0);
	//if (!validate_newline(command))
	//	return (0);
	tokens = split_tokens(command->content, command->length);
	if (tokens == NULL)
		return (-1);
	if (!create_instruction(instruction, tokens))
	{
		clear_tokens(tokens);
		return (-1);
	}
	flag = parse_pipeline(instruction->pipelines, tokens);
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

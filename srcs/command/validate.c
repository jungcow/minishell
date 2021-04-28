/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoh <seunghoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 20:15:17 by seunghoh          #+#    #+#             */
/*   Updated: 2021/04/27 22:49:57 by seunghoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdbool.h>
#include "command/command.h"
#include "error/error.h"

static int	validate_token(t_command *command, int token_start, int token_end)
{
	bool	is_space;
	
	command->quote_status = false;
	is_space = true;
	while (token_start < token_end)
	{
		if (command->line.content[token_start] != ' ')
			is_space = false;
		if (command->line.content[token_start] == QUOTE ||
			command->line.content[token_start] == DOUBLE_QUOTE)
			command->quote_status = !command->quote_status;
		token_start++;
	}
	if (is_space)
		return (-1);
	else if (command->quote_status)
		return (0);
	else
		return (1);
}

bool		validate_command(t_command *command)
{
	int		token_start;
	int		token_end;
	int		flag;

	token_start = 0;
	token_end = 0;
	while (token_end < command->line.length)
	{
		flag = 0;
		if (command->line.content[token_end] == ';')
			flag = validate_token(command, token_start, token_end);
		if (flag == -1)
		{
			write(1, SEMICOLON_TOKEN_ERR, ft_strlen(SEMICOLON_TOKEN_ERR));
			return (false);
		}
		else if (flag == 1)
		{
			token_start = token_end + 1;
			command->line.content[token_end] = '\0';
		}
		token_end++;
	}
	return (true);
}

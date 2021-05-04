/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoh <seunghoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 20:17:01 by seunghoh          #+#    #+#             */
/*   Updated: 2021/05/04 18:10:07 by seunghoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "command/command.h"
#include "error/error.h"

static char	*dump_command(t_command *command)
{
	int		i;
	char	quote_status;
	char	*dump;

	dump = ft_strdup(command->line.content);
	if (dump == NULL)
		return (NULL);
	i = 0;
	quote_status = 0;
	while (dump[i] != '\0')
	{
		if (dump[i] == QUOTE || dump[i] == DOUBLE_QUOTE)
		{
			if (quote_status == 0)
				quote_status = dump[i];
			else if (quote_status == dump[i])
				quote_status = 0;
			dump[i] = '*';
		}
		else if (quote_status)
			dump[i] = '*';
		i++;
	}
	return (dump);
}

static bool	validate_token(char *dump)
{
	int		i;
	bool	flag;

	i = 0;
	flag = true;
	while (dump[i] != '\0')
	{
		if (dump[i] == ';')
			flag = validate_semicolon(dump, i);
		else if (dump[i] == '|')
			flag = validate_pipe(dump, i);
		else if (dump[i] == '<' || dump[i] == '>')
		{
			flag = validate_redirect(dump, i);
			if (dump[i] == '>' && dump[i + 1] == '>')
				i++;
		}
		if (flag == false)
			return (false);
		i++;
	}
	flag = validate_newline(dump, i);
	return (flag);
}

bool		validate_quote(char *dump, int length)
{
	int		i;
	int		quote_status;

	i = 0;
	quote_status = 0;
	while (i < length)
	{
		if (dump[i] == QUOTE || dump[i] == DOUBLE_QUOTE)
		{
			if (quote_status == 0)
				quote_status = dump[i];
			else if (quote_status == dump[i])
				quote_status = 0;
		}
		i++;
	}
	if (quote_status != 0)
	{
		unexpected_token(NEWLINE);
		return (false);
	}
	return (true);
}

bool		validate_command(t_command *command)
{
	char	*dump;
	bool	flag;

	refactor_command(command);
	if (empty_command(command))
	{
		command->line.length = 1;
		return (true);
	}
	dump = dump_command(command);
	if (dump == NULL)
		return (false);
	flag = validate_token(dump);
	free(dump);
	flag = flag && validate_quote(command->line.content,
									command->line.length);
	if (flag == false)
		command->line.length = 1;
	return (true);
}

bool		validate_newline(char *dump, int pos)
{
	bool	is_space;
	int		i;

	i = pos - 1;
	is_space = true;
	while (i >= 0)
	{
		if (ft_strchr("<>|", dump[i]) != NULL)
			break ;
		if (ft_strchr(" \n", dump[i]) == NULL)
			is_space = false;
		i--;
	}
	if (is_space)
		unexpected_token(NEWLINE);
	return (!is_space);
}

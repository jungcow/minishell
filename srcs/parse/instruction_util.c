/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_util.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoh <seunghoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 23:16:23 by seunghoh          #+#    #+#             */
/*   Updated: 2021/04/28 23:27:54 by seunghoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "libft.h"
#include "parse/parse_util.h"
#include "error/error.h"

bool	validate_instruction(t_string *command)
{
	int		i;
	bool	is_space;

	i = 0;
	is_space = true;
	while (i < command->length)
	{
		if (command->content[i] == ';')
		{
			if (is_space)
			{
				write(1, SEMICOLON_TOKEN_ERR, ft_strlen(SEMICOLON_TOKEN_ERR));
				return (false);
			}
			command->content[i] = '\0';
			is_space = true;
		}
		else
			i = skip_space_quote(command, i, &is_space);
		i++;
	}
	return (true);
}

bool	validate_newline(t_string *command)
{
	int		i;

	i = command->length - 2;
	
	while (i >= 0)
	{
		if (command->content[i] != ' ')
			break ;
		i--;
	}
	if (i < 0)
		return (true);
	if (ft_strchr("<>|", command->content[i]) != NULL)
	{
		write(1, NEWLINE_TOKEN_ERR, ft_strlen(NEWLINE_TOKEN_ERR));
		return (0);
	}
	return (true);
}

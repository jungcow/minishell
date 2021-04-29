/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoh <seunghoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 19:51:29 by seunghoh          #+#    #+#             */
/*   Updated: 2021/04/29 02:21:45 by seunghoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		skip_quote(char *str, int length, int start)
{
	start++;
	while (start < length)
	{
		if (str[start] == 34)
			break ;
		start++;
	}
	return (start);
}

int		skip_dquote(char *str, int length, int start)
{
	start++;
	while (start < length)
	{
		if (str[start] == 39)
			break ;
		start++;
	}
	return (start);
}

int		skip_space(char *str, int length, int start)
{
	while (start < length)
	{
		if (str[start] != ' ')
			return (start - 1);
		start++;
	}
	return (start);
}

int		skip_space_quote(t_string *command, int i, bool *is_space)
{
	if (command->content[i] == ' ')
		i = skip_space(command->content, command->length, i);
	else
	{
		*is_space = false;
		if (command->content[i] == 34)
			i = skip_quote(command->content, command->length, i);
		else if (command->content[i] == 39)
			i = skip_dquote(command->content, command->length, i);
		else if (command->content[i] == '|' ||
				command->content[i] == '<' ||
				command->content[i] == '>')
		{
			if (i > 0 && command->content[i] == '|' &&
					command->content[i - 1] == '>')
				command->content[i] = ' ';
			*is_space = true;
		}
	}
	return (i);
}

int		skip_pipeline(char *token, int i, bool *is_space)
{
	if (token[i] == ' ')
		i = skip_space(token, ft_strlen(token), i);
	else
	{
		*is_space = false;
		if (token[i] == 34)
			i = skip_quote(token, ft_strlen(token), i);
		else if (token[i] == 39)
			i = skip_dquote(token, ft_strlen(token), i);
		else if (token[i] == '<' ||
				token[i] == '>')
		{
			*is_space = true;
		}
	}
	return (i);
}

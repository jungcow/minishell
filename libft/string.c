/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoh <seunghoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 03:47:09 by seunghoh          #+#    #+#             */
/*   Updated: 2021/04/16 17:00:20 by seunghoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include "libft.h"
#include "string.h"

bool	init_string(t_string *string)
{
	string->length = 0;
	string->capacity = 0;
	string->content = (char *)malloc(sizeof(char) * STRING_SIZE);
	if (string->content == NULL)
		return (false);
	string->capacity = STRING_SIZE;
	return (true);
}

bool	add_string(t_string *string, int index, char ch)
{
	char	*temp;
	int		i;

	if (index < 0 || index > string->length)
		return (false);
	if (string->length == string->capacity)
	{
		temp = (char *)malloc(sizeof(char) * (string->capacity + STRING_SIZE));
		if (temp == NULL)
			return (false);
		ft_strncpy(temp, string->content, string->capacity);
		free(string->content);
		string->content = temp;
		string->capacity += STRING_SIZE;
	}
	i = string->length + 1;
	while (--i > index)
		string->content[i] = string->content[i - 1];
	string->content[index] = ch;
	string->length++;
	return (true);
}

bool	delete_string(t_string *string, int index, char *ch)
{
	if (index < 0 || index >= string->length)
		return (false);
	*ch = string->content[index];
	while (index + 1 < string->length)
	{
		string->content[index] = string->content[index + 1];
		index++;
	}
	string->length--;
	return (true);
}

void	clear_string(t_string *string)
{
	free(string->content);
	string->content = NULL;
	string->length = 0;
	string->capacity = 0;
}

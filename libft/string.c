/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoh <seunghoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 03:47:09 by seunghoh          #+#    #+#             */
/*   Updated: 2021/04/15 20:26:25 by seunghoh         ###   ########.fr       */
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

bool	add_string(t_string *string, char ch)
{
	char	*temp;

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
	string->content[string->length++] = ch;
	return (true);
}

void	clear_string(t_string *string)
{
	free(string->content);
	string->content = NULL;
	string->length = 0;
	string->capacity = 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoh <seunghoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 19:51:29 by seunghoh          #+#    #+#             */
/*   Updated: 2021/05/13 16:48:47 by seunghoh         ###   ########.fr       */
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
		if (str[start] == 39 && str[start - 1] != '\\')
			break ;
		start++;
	}
	return (start);
}

int		skip_space(char *str, int length, int start)
{
	while (start < length)
	{
		if (str[start] != ' ' && str[start] != '\n')
			return (start - 1);
		start++;
	}
	return (start);
}

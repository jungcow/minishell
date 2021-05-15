/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoh <seunghoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 19:51:29 by seunghoh          #+#    #+#             */
/*   Updated: 2021/05/15 13:31:43 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		skip_quote(char *str, int length, int start)
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

int		skip_dquote(char *str, int length, int start)
{
	int		i;
	int		j;

	i = 0;
	start++;
	while (start < length)
	{
		j = 1;
		if (str[start] == 34)
			while (str[start - j] == '\\')
				j++;
		if (j % 2 == 1)
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

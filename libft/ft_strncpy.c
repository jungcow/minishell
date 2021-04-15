/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoh <seunghoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 20:07:34 by seunghoh          #+#    #+#             */
/*   Updated: 2021/04/15 20:16:24 by seunghoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	ft_strncpy(char *dest, const char *src, int size)
{
	int	idx;

	idx = 0;
	if (src == NULL || dest == NULL)
		return ;
	while (idx < size)
	{
		dest[idx] = src[idx];
		idx++;
	}
}

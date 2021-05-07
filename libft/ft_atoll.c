/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoh <seunghoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 18:47:29 by seunghoh          #+#    #+#             */
/*   Updated: 2021/05/07 18:58:15 by seunghoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	get_offset(char *str)
{
	long long	offset;

	offset = 0;
	if (ft_strcmp(str, "-9223372036854775808") == 0)
	{
		str[ft_strlen(str) - 1] = '7';
		offset = 1;
	}
	return (offset);
}

long long	ft_atoll(char *str)
{
	long long	sign;
	long long	sum;
	long long	offset;

	sign = 1;
	sum = 0;
	offset = get_offset(str);
	while (ft_isspace(*str) && *str)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit(*str) && *str)
	{
		if (sum < 0)
			return ((sign < 0) ? 0 : -1);
		sum = sum * 10 + *str - '0';
		str++;
	}
	sum += offset;
	return (sum * sign);
}

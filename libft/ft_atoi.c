/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungwkim <jungwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 18:22:13 by jungwkim          #+#    #+#             */
/*   Updated: 2021/03/22 20:13:24 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ft_atoi(const char *str)
{
	int		sign;
	int		sum;

	sign = 1;
	sum = 0;
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
	return (sum * sign);
}

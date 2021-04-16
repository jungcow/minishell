/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungwkim <jungwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 19:51:42 by jungwkim          #+#    #+#             */
/*   Updated: 2020/12/29 15:40:17 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	count_digits(unsigned int n, unsigned int *k)
{
	if (n >= 10)
	{
		*k += 1;
		count_digits(n / 10, k);
	}
	else
		return ;
}

static void	put_num_str(char *str, unsigned int n)
{
	if (n < 10)
	{
		*str = n % 10 + '0';
		return ;
	}
	put_num_str(str - 1, n / 10);
	*str = n % 10 + '0';
}

char		*ft_itoa(int n)
{
	unsigned int	k;
	unsigned int	num;
	char			*str;

	k = 1;
	if (n < 0)
		num = n * (-1);
	else
		num = n;
	count_digits(num, &k);
	str = n < 0 ? (char *)malloc(sizeof(char) * (k + 2))
		: (char *)malloc(sizeof(char) * (k + 1));
	if (str == 0)
		return (0);
	if (n < 0)
	{
		k = k + 1;
		str[0] = '-';
	}
	put_num_str(str + k - 1, num);
	str[k] = '\0';
	return (str);
}

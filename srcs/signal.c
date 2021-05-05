/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoh <seunghoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 16:39:04 by seunghoh          #+#    #+#             */
/*   Updated: 2021/05/05 21:09:24 by seunghoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "builtin.h"

// ctrl + D only buffer is empty

void	sigint_handler(void)
{
	printf("siginal inturrupt!\n");
	//ft_exit(1, NULL, NULL);
}

void	sigquit_handler(void)
{
	printf("siginal quit!\n");
	ft_exit(1, NULL, NULL);
}

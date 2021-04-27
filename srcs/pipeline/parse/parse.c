/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoh <seunghoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 17:48:53 by seunghoh          #+#    #+#             */
/*   Updated: 2021/04/28 00:44:33 by seunghoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

int		parse_pipeline(char	*token)
{
    printf("\nToken : [");
	while (*token != '\0')
		printf("%c", *token++);
    printf("]\n");
	return (0);
}

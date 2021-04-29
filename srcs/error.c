/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoh <seunghoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 23:27:47 by seunghoh          #+#    #+#             */
/*   Updated: 2021/04/30 00:06:28 by seunghoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "error/error.h"

void	unexpected_token(char *token)
{
	write(2, TOKEN_ERR, ft_strlen(TOKEN_ERR));
	write(2, " '", 2);
	write(2, token, ft_strlen(token));
	write(2, "'\n", 2);
}

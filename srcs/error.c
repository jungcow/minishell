/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoh <seunghoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 23:27:47 by seunghoh          #+#    #+#             */
/*   Updated: 2021/05/04 01:49:10 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "error/error.h"

void	command_not_found(char *command)
{
	write(2, COMMAND_ERR_FRONT, ft_strlen(COMMAND_ERR_FRONT));
	write(2, command, ft_strlen(command));
	write(2, COMMAND_ERR_BACK, ft_strlen(COMMAND_ERR_BACK));
	write(1, "\n", 1);
}

void	unexpected_token(char *token)
{
	write(2, TOKEN_ERR, ft_strlen(TOKEN_ERR));
	write(2, " '", 2);
	write(2, token, ft_strlen(token));
	write(2, "'\n", 2);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoh <seunghoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 23:27:47 by seunghoh          #+#    #+#             */
/*   Updated: 2021/05/07 16:38:45 by seunghoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "error/error.h"
#include "execute/execute.h"

void	command_error(char *command, int err_type)
{
	write(2, ERR_HEAD, ft_strlen(ERR_HEAD));
	write(2, command, ft_strlen(command));
	if (err_type == 0)
		write(2, COMMAND_ERR, ft_strlen(COMMAND_ERR));
	else if (err_type == DIRECTORY)
		write(2, DIRECTORY_ERR, ft_strlen(DIRECTORY_ERR));
	else if (err_type == PERMISSION)
		write(2, PERMISSION_ERR, ft_strlen(PERMISSION_ERR));
	else if (err_type == NO_SUCH)
		write(2, NO_SUCH_ERR, ft_strlen(NO_SUCH_ERR));
	write(1, "\n", 1);
}

void	unexpected_token(char *token)
{
	write(2, TOKEN_ERR, ft_strlen(TOKEN_ERR));
	write(2, " '", 2);
	write(2, token, ft_strlen(token));
	write(2, "'\n", 2);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoh <seunghoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 23:27:47 by seunghoh          #+#    #+#             */
/*   Updated: 2021/05/08 16:28:47 by jungwkim         ###   ########.fr       */
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
	write(1, "'\n", 2); //이거 개행 fd 2번에 찍히나요??
}

void	invalid_identifier(char *arg)
{
	write(2, ERR_HEAD, ft_strlen(ERR_HEAD));
	write(2, "\'", 1);
	write(2, arg, ft_strlen(arg));
	write(2, "\'", 1);
	write(2, INVALID_IDENTIFIER_ERR, ft_strlen(INVALID_IDENTIFIER_ERR));
	write(1, "\n", 1);
}

void	invalid_argument(char *arg, int err_type)
{
	write(2, ENV_ERR, ft_strlen(ENV_ERR));
	if (err_type == 1)
		write(2, SETENV, ft_strlen(SETENV));
	write(2, arg, ft_strlen(arg));
	if (err_type == 1)
		write(2, INVALID_ARGUMENT_ERR, ft_strlen(INVALID_ARGUMENT_ERR));
	else
		write(2, NO_SUCH_ERR, ft_strlen(NO_SUCH_ERR));
	write(1, "\n", 1);
}

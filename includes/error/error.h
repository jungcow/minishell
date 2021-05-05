/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoh <seunghoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 21:24:19 by seunghoh          #+#    #+#             */
/*   Updated: 2021/05/06 02:17:40 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define MINISH_ERR "minish: "
# define SEMICOLON ";"
# define D_SEMICOLON ";;"
# define PIPE "|"
# define D_PIPE "||"
# define NEWLINE "newline"
# define IN_REDIRECT "<"
# define D_IN_REDIRECT "<<"
# define T_IN_REDIRECT "<<<"
# define OUT_REDIRECT ">"
# define D_OUT_REDIRECT ">>"
# define TOKEN_ERR "minish: syntax error near unexpected token"
# define COMMAND_ERR ": command not found"
# define DIRECTORY_ERR ": is a directory"
# define PERMISSION_ERR ": Permission denied"
# define NO_SUCH_ERR ": No such file or directory"

void	command_error(char *command, int err_type);
void	unexpected_token(char *token);

#endif

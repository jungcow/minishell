/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoh <seunghoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 21:24:19 by seunghoh          #+#    #+#             */
/*   Updated: 2021/05/07 21:11:59 by seunghoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define LONGLONG_MAX "9223372036854775807"
# define LONGLONG_MIN "9223372036854775808"

# define ERR_HEAD "imposter: "
# define SEMICOLON ";"
# define EXIT_ERR "exit: "
# define CD_HOME_ERR "HOME not set"
# define CD_ERR "cd : "
# define CD_CWD_ERR "error retrieving current directory : getcwd: cannot access parent directories : No such file or directory"
# define EXIT_NUMERIC_ERR "numeric argument required"
# define EXIT_ARGV_ERR "too many arguments"
# define D_SEMICOLON ";;"
# define PIPE "|"
# define D_PIPE "||"
# define NEWLINE "newline"
# define IN_REDIRECT "<"
# define D_IN_REDIRECT "<<"
# define T_IN_REDIRECT "<<<"
# define OUT_REDIRECT ">"
# define D_OUT_REDIRECT ">>"
# define TOKEN_ERR "imposter: syntax error near unexpected token"
# define COMMAND_ERR ": command not found"
# define DIRECTORY_ERR ": is a directory"
# define PERMISSION_ERR ": Permission denied"
# define NO_SUCH_ERR ": No such file or directory"

void	command_error(char *command, int err_type);
void	unexpected_token(char *token);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoh <seunghoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 21:24:19 by seunghoh          #+#    #+#             */
/*   Updated: 2021/05/04 01:52:51 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

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
# define COMMAND_ERR_FRONT "minish: "
# define COMMAND_ERR_BACK ": command not found"

void	command_not_found(char *command);
void	unexpected_token(char *token);

#endif

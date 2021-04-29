/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoh <seunghoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 21:24:19 by seunghoh          #+#    #+#             */
/*   Updated: 2021/04/29 23:31:02 by seunghoh         ###   ########.fr       */
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
# define TOKEN_ERR "bash: syntax error near unexpected token"

void	unexpected_token(char *token);

#endif

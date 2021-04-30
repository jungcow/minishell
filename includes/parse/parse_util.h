/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoh <seunghoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 19:56:31 by seunghoh          #+#    #+#             */
/*   Updated: 2021/05/01 04:08:18 by seunghoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_UTIL_H
# define PARSE_UTIL_H

# include <stdbool.h>
# include "libft.h"

int		skip_quote(char *str, int length, int start);
int		skip_dquote(char *str, int length, int start);
int		skip_space(char *str, int length, int start);
char	**split_tokens(char *line, int length);
void	clear_tokens(char **tokens);

#endif

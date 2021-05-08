/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoh <seunghoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 03:51:30 by seunghoh          #+#    #+#             */
/*   Updated: 2021/05/08 17:17:47 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include "get_next_line.h"
# include "string.h"

size_t		ft_strlen(const char *str);
size_t		ft_strslen(char **strs);

char		**ft_split(char const *s, char c);
char		*ft_strdup(const char *s);
void		ft_strsfree(char **strs);
int			ft_strswap(char **s1, char **s2);

char		*ft_itoa(int n);
int			ft_atoi(const char *str);
long long	ft_atoll(char *str);

int			ft_isspace(int c);
int			ft_isdigit(int c);
int			ft_isalpha(int c);
int			ft_isalnum(int c);

void		ft_strncpy(char *dest, const char *src, int size);
char		*ft_strchr(const char *s, int c);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strjoin(const char *s1, const char *s2);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungwkim <jungwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 04:25:29 by jungwkim          #+#    #+#             */
/*   Updated: 2021/05/02 04:32:49 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRON_H
# define ENVIRON_H

int		create_envset(char ***envset, char *arg, int *flag);
int		init_envset(char **envset, char *arg, int flag);
int		replace_envset(char **envset, char *arg);
int		join_envset(char **envset, char **arg);

/*
**		utils
*/
int		dup_envset(char **env, char *str);
int		count_envset(char *arg);
void	clear_envset(char **envset);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoh <seunghoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 18:35:17 by seunghoh          #+#    #+#             */
/*   Updated: 2021/05/11 16:14:25 by seunghoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "environ/environ.h"

int		ft_echo(int argc, char **argv, t_environ *environ);
int		ft_pwd(void);
int		ft_cd(int argc, char **argv);
int		ft_export(int argc, char **argv, t_environ *environ);
int		ft_unset(int argc, char **argv, t_environ **environ);
int		ft_env(int argc, char **argv, t_environ *environ);
int		ft_exit(int argc, char **argv);
int		ft_history(void);

/*
**		utils
*/
void	update_pwd(char **argv);
int		alloc_env_value(char *key, char ***argv, char **value, int *flag);
int		write_original_environ(t_environ *environ, char ***argv);
void	success_getcwd(void);
void	fail_getcwd(char **argv);

#endif

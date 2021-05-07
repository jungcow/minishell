/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoh <seunghoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 18:35:17 by seunghoh          #+#    #+#             */
/*   Updated: 2021/05/07 17:00:03 by seunghoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

int		ft_echo(int argc, char **argv, char **env);
int		ft_pwd(void);
int		ft_cd(int argc, char **argv, char **env);
int		ft_export(int argc, char **argv, char **env);
int		ft_unset(int argc, char **argv, char **env);
int		ft_env(int argc, char **argv, char **env);
int		ft_exit(int argc, char **argv);

#endif

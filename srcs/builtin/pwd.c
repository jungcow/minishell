/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoh <seunghoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 18:22:56 by seunghoh          #+#    #+#             */
/*   Updated: 2021/05/07 19:51:06 by seunghoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "command/command.h"

extern t_command	g_command;

int		ft_pwd(void)
{
	write(1, g_command.pwd, ft_strlen(g_command.pwd));
	write(1, "\n", 1);
	return (0);
}

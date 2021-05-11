/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoh <seunghoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 18:22:56 by seunghoh          #+#    #+#             */
/*   Updated: 2021/05/11 11:32:10 by seunghoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "libft.h"
#include "command/command.h"

extern t_command	g_command;

int		ft_pwd(void)
{
	if (g_command.pwd == NULL)
		return (1);
	write(1, g_command.pwd, ft_strlen(g_command.pwd));
	write(1, "\n", 1);
	return (0);
}

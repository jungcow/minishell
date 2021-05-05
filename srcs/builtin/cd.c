/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoh <seunghoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 18:33:25 by seunghoh          #+#    #+#             */
/*   Updated: 2021/05/05 18:45:31 by seunghoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// if argv[1] == NULL ??
#include <unistd.h>

int		ft_cd(int argc, char **argv)
{
	if (chdir(argv[1]) == -1)
	{
		// NO SUCH FILE OR DIRECTORY
		return (1);
	}
	return (0);
}

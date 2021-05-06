/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoh <seunghoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 18:33:25 by seunghoh          #+#    #+#             */
/*   Updated: 2021/05/06 07:32:58 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// if argv[1] == NULL ??
#include <unistd.h>
#include <stdlib.h>
#include "error/error.h"
#include "execute/execute.h"

int		ft_cd(int argc, char **argv)
{
	argc = 0;
	if (argv[1] == NULL)
		argv[1] = getenv("HOME");
	if (chdir(argv[1]) == -1)
	{
		command_error(argv[0], NO_SUCH);
		// NO SUCH FILE OR DIRECTORY
		return (1);
	}
	return (0);
}

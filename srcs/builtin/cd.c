/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoh <seunghoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 18:33:25 by seunghoh          #+#    #+#             */
/*   Updated: 2021/05/07 12:59:39 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		return (1);
	}
	return (0);
}

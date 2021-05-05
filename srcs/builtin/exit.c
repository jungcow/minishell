/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoh <seunghoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 16:48:48 by seunghoh          #+#    #+#             */
/*   Updated: 2021/05/05 18:30:21 by seunghoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

// if argv[1] != ONLY NUMBER
// bash: exit: a: numeric argument required / code : 255
// bash: exit: too many arguments
// bash: exit: -1도 가능 alphabet이 들어가면 안됨

int		ft_exit(int argc, char **argv, char **envp)
{
	int		err;

	(void)envp;
	err = 0;
	(void)argc;
	(void)argv;
	/*
	if (argc > 1)
	{
		check_argument(argv[1]);
		err = ft_atoi(argv[1]);
	}*/
	exit(err);
	return (0);
}

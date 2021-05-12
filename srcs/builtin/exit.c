/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoh <seunghoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 16:48:48 by seunghoh          #+#    #+#             */
/*   Updated: 2021/05/12 10:30:08 by seunghoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "error/error.h"
#include "libft.h"

void	check_numeric(char *arg)
{
	int		i;

	i = 0;
	if (arg[i] == '-')
		i++;
	while (ft_isdigit(arg[i]))
		i++;
	if (arg[i] == '\0')
		return ;
	write(2, ERR_HEAD, ft_strlen(ERR_HEAD));
	write(2, EXIT_ERR, ft_strlen(EXIT_ERR));
	write(2, arg, ft_strlen(arg));
	write(2, ": ", 2);
	write(2, EXIT_NUMERIC_ERR, ft_strlen(EXIT_NUMERIC_ERR));
	write(2, "\n", 1);
	exit(255);
}

void	check_length(char *arg)
{
	if (ft_strlen(arg) > ft_strlen(LONGLONG_MAX) ||
		ft_strcmp(LONGLONG_MAX, arg) < 0)
	{
		write(2, ERR_HEAD, ft_strlen(ERR_HEAD));
		write(2, EXIT_ERR, ft_strlen(EXIT_ERR));
		write(2, arg, ft_strlen(arg));
		write(2, ": ", 2);
		write(2, EXIT_NUMERIC_ERR, ft_strlen(EXIT_NUMERIC_ERR));
		write(1, "\n", 1);
		exit(255);
	}
}

void	check_m_length(char *arg)
{
	arg++;
	if (ft_strlen(arg) > ft_strlen(LONGLONG_MIN) ||
		ft_strcmp(LONGLONG_MIN, arg) < 0)
	{
		write(2, ERR_HEAD, ft_strlen(ERR_HEAD));
		write(2, EXIT_ERR, ft_strlen(EXIT_ERR));
		write(2, arg - 1, ft_strlen(arg - 1));
		write(2, ": ", 2);
		write(2, EXIT_NUMERIC_ERR, ft_strlen(EXIT_NUMERIC_ERR));
		write(1, "\n", 1);
		exit(255);
	}
}

int		check_argc(int argc)
{
	if (argc < 3)
		return (0);
	write(2, ERR_HEAD, ft_strlen(ERR_HEAD));
	write(2, EXIT_ERR, ft_strlen(EXIT_ERR));
	write(2, EXIT_ARGV_ERR, ft_strlen(EXIT_ARGV_ERR));
	write(1, "\n", 1);
	return (1);
}

int		ft_exit(int argc, char **argv)
{
	if (argc > 1)
	{
		check_numeric(argv[1]);
		if (argv[1][0] == '-')
			check_m_length(argv[1]);
		else
			check_length(argv[1]);
		if (check_argc(argc))
			return (1);
		exit(ft_atoll(argv[1]));
	}
	exit(0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungwkim <jungwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 11:54:25 by jungwkim          #+#    #+#             */
/*   Updated: 2021/05/08 18:05:37 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include "error/error.h"
#include "builtin.h"
#include "libft.h"

int		validate_env_argv(char **argv, char **arg)
{
	while (*argv)
	{
		if (ft_strchr(*argv, '=') == NULL)
		{
			*arg = *argv;
			return (127);
		}
		else if (**argv == '=')
		{
			*arg = *argv;
			return (1);
		}
		argv++;
	}
	return (0);
}

void	write_entire_environ(t_environ *environ)
{
	while (environ)
	{
		if (ft_strchr(environ->env, '='))
		{
			write(1, environ->env, ft_strlen(environ->env));
			write(1, "\n", 1);
		}
		environ = environ->next;
	}
}

int		ft_env(int argc, char **argv, t_environ *environ)
{
	char	*arg;
	int		i;
	int		ret;

	if (argc > 1)
	{
		ret = validate_env_argv(argv + 1, &arg);
		if (ret == 1 || ret == 127)
		{
			invalid_argument(arg, ret);
			return (ret);
		}
		write_entire_environ(environ);
		i = 0;
		while (argv[++i])
		{
			write(1, argv[i], ft_strlen(argv[i]));
			write(1, "\n", 1);
		}
	}
	if (argc == 1)
		write_entire_environ(environ);
	return (errno);
}

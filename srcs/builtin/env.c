/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungwkim <jungwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 11:54:25 by jungwkim          #+#    #+#             */
/*   Updated: 2021/05/07 22:02:22 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include "environ/environ.h"
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
			return (-1);
		}
		else if (**argv == '=')
		{
			*arg = *argv;
			return (0);
		}
		argv++;
	}
	return (1);
}

void	write_entire_environ(t_environ *environ)
{
	while (environ)
	{
		write(1, environ->env, ft_strlen(environ->env));
		write(1, "\n", 1);
		environ = environ->next;
	}
}

int		write_error_environ(char *arg, int ret)
{
	write(1, "env: ", ft_strlen("env: "));
	if (ret == 0)
		write(1, "setenv ", ft_strlen("setenv "));
	write(1, arg, ft_strlen(arg));
	write(1, ": ", 2);
	if (ret == 0)
		write(1, "Invalid argument", ft_strlen("Invalid argument"));
	else	
		write(1, NO_SUCH_ERR, ft_strlen(NO_SUCH_ERR));
	write(1, "\n", 1);
	if (ret == 0)
		return (1);
	return (127);
}

int		ft_env(int argc, char **argv, t_environ *environ)
{
	char	*arg;
	int		i;
	int		ret;

	if (argc > 1)
	{
		ret = validate_env_argv(argv + 1, &arg);
		if (ret == -1 || ret == 0)
			return (write_error_environ(arg, ret));
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

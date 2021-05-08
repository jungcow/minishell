/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungwkim <jungwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 11:54:25 by jungwkim          #+#    #+#             */
/*   Updated: 2021/05/09 02:18:17 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
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

int		write_entire_environ(t_environ *environ, char **argv)
{
	int		i;

	if (write_original_environ(environ, &argv) < 0)
		return (-1);
	i = -1;
	while (argv && argv[++i])
	{
		write(1, argv[i], ft_strlen(argv[i]));
		write(1, "\n", 1);
	}
	ft_strsfree(argv);
	return (0);
}

int		ft_env(int argc, char **argv, t_environ *environ)
{
	char	*arg;
	char	**new;
	int		ret;

	new = (char **)malloc(sizeof(char *) * (argc));
	ret = -1;
	while (++ret < argc)
		new[ret] = NULL;
	ret = -1;
	while (++ret < argc - 1)
	{
		new[ret] = ft_strdup(argv[ret + 1]);
		if (new[ret] == NULL)
			return (-1);
	}
	if (argc > 1)
	{
		ret = validate_env_argv(argv + 1, &arg);
		if (ret == 1 || ret == 127)
		{
			invalid_argument(arg, ret);
			return (ret);
		}
	}
	return (write_entire_environ(environ, new));
}

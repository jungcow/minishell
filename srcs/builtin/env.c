/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungwkim <jungwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 11:54:25 by jungwkim          #+#    #+#             */
/*   Updated: 2021/05/11 21:22:41 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "error/error.h"
#include "builtin.h"
#include "libft.h"

int		validate_env_argv(char **argv, char *arg, int i)
{
	int		ret;

	ret = 0;
	while (argv[++i])
	{
		if (ft_strchr(argv[i], '=') == NULL)
		{
			arg = argv[i];
			ret = 127;
			break ;
		}
		else if (*(argv[i]) == '=')
		{
			arg = argv[i];
			ret = 1;
			break ;
		}
	}
	if (ret)
	{
		invalid_argument(arg, ret);
		ft_strsfree(argv);
	}
	return (ret);
}

int		search_key_buf(char **buf, char *str)
{
	int		i;
	char	*ptr;
	char	*key;

	ptr = ft_strlchr(str, '=');
	if (!ptr)
		return (0);
	key = ft_strndup(str, ptr - str);
	if (!key)
		exit(-1);
	i = -1;
	while (buf[++i])
		if (!ft_strcmp(buf[i], key))
		{
			free(key);
			return (1);
		}
	buf[i] = key;
	return (0);
}

int		write_entire_environ(t_environ *environ, char **argv)
{
	int		i;
	char	**buf;

	if (write_original_environ(environ, &argv) < 0)
		return (-1);
	i = -1;
	if (argv == NULL)
		return (0);
	buf = (char **)malloc(sizeof(char *) * (ft_strslen(argv) + 1));
	if (!buf)
		return (-1);
	while (++i < (int)ft_strslen(argv))
		buf[i] = NULL;
	buf[i] = NULL;
	i = ft_strslen(argv);
	while (argv && i && argv[--i])
		if (!search_key_buf(buf, argv[i]))
		{
			write(1, argv[i], ft_strlen(argv[i]));
			write(1, "\n", 1);
		}
	ft_strsfree(buf);
	ft_strsfree(argv);
	return (0);
}

int		ft_env(int argc, char **argv, t_environ *environ)
{
	char	**new;
	char	*arg;
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
	arg = NULL;
	if (argc > 1)
	{
		ret = validate_env_argv(new, arg, -1);
		if (ret)
			return (ret);
	}
	return (write_entire_environ(environ, new));
}

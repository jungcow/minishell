/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungwkim <jungwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 12:24:21 by jungwkim          #+#    #+#             */
/*   Updated: 2021/05/08 17:59:36 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>
#include "error/error.h"
#include "environ/environ.h"
#include "libft.h"
#include "builtin.h"

void	write_env_export(char *key, char *value, char *flag)
{
	write(1, "declare -x ", ft_strlen("declare -x "));
	write(1, key, ft_strlen(key));
	if (flag)
	{
		write(1, "=", 1);
		write(1, "\"", 1);
		if (value)
			write(1, value, ft_strlen(value));
		write(1, "\"", 1);
	}
	write(1, "\n", 1);
}

int		change_value_export(t_environ *environ, char *value)
{
	char	**strs;
	char	*key;

	strs = ft_split(environ->env, '=');
	if (strs == NULL)
		return (-1);
	key = ft_strjoin(strs[0], "=");
	if (key == NULL)
	{
		ft_strsfree(strs);
		return (-1);
	}
	free(environ->env);
	if (value == NULL)
		environ->env = ft_strjoin(key, "");
	else
		environ->env = ft_strjoin(key, value);
	if (environ->env == NULL)
	{
		ft_strsfree(strs);
		return (-1);
	}
	ft_strsfree(strs);
	return (1);
}

int		search_value_export(t_environ *environ, char *arg)
{
	char	**env_tmp;
	char	**arg_tmp;
	int		flag;

	flag = 0;
	while (environ)
	{
		env_tmp = ft_split(environ->env, '=');
		arg_tmp = ft_split(arg, '=');
		if (!env_tmp || !arg_tmp)
			return (-1);
		if (ft_strcmp(env_tmp[0], arg_tmp[0]) == 0)
		{
			flag = 1;
			if (ft_strchr(arg, '='))
				change_value_export(environ, arg_tmp[1]);
			break ;
		}
		environ = environ->next;
	}
	ft_strsfree(env_tmp);
	ft_strsfree(arg_tmp);
	if (!flag)
		return (0);
	return (1);
}

int		apply_export_argv(t_environ *environ, char **argv)
{
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	while (argv[++i])
	{
		if (!ft_isalpha(*(argv[i])) && *(argv[i]) != '_')
		{
			invalid_identifier(argv[i]);
			flag = 1;
			continue ;
		}
		if (!search_value_export(environ, argv[i]))
		{
			if (!alloc_environ(&environ, argv[i]))
				return (-1);
		}
	}
	return (flag);
}

int		ft_export(int argc, char **argv, t_environ *environ)
{
	char	**strs;
	int		i;
	char	**envstrs;

	if (argc > 1)
		return (apply_export_argv(environ, argv));
	if (list_to_strs_environ(environ, &envstrs) < 0 ||
			!bubble_sort_environ(envstrs))
		return (-1);
	i = 0;
	while (envstrs[i])
	{
		strs = ft_split(envstrs[i], '=');
		if (strs == NULL)
		{
			ft_strsfree(envstrs);
			return (-1);
		}
		write_env_export(strs[0], strs[1], ft_strchr(envstrs[i], '='));
		ft_strsfree(strs);
		i++;
	}
	ft_strsfree(envstrs);
	return (0);
}

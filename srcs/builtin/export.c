/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungwkim <jungwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 12:24:21 by jungwkim          #+#    #+#             */
/*   Updated: 2021/05/11 20:39:32 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "error/error.h"
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
	char	*str;
	char	*ptr;
	char	*key;

	ptr = ft_strlchr(environ->env, '=');
	str = ft_strndup(environ->env, ptr - environ->env);
	if (str == NULL)
		return (-1);
	key = ft_strjoin(str, "=");
	free(str);
	if (key == NULL)
		exit(-1);
	free(environ->env);
	if (value == NULL)
		environ->env = ft_strjoin(key, "");
	else
		environ->env = ft_strjoin(key, value);
	if (environ->env == NULL)
		exit(-1);
	free(key);
	return (1);
}

int		search_value_export(t_environ *environ, char *arg)
{
	char	*ptr;
	char	*arg_key;
	char	*env_key;
	int		flag;

	flag = 0;
	while (environ && flag == 0)
	{
		ptr = ft_strlchr(environ->env, '=');
		env_key = ft_strndup(environ->env, ptr - environ->env);
		ptr = ft_strlchr(arg, '=');
		arg_key = ft_strndup(arg, ptr - arg);
		if (!env_key || !arg_key)
			exit(1);
		if (ft_strcmp(env_key, arg_key) == 0)
		{
			flag = 1;
			if (ft_strchr(arg, '='))
				change_value_export(environ, ptr + 1);
		}
		free(env_key);
		free(arg_key);
		environ = environ->next;
	}
	return (flag);
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
			continue ;
		}
	}
	return (flag);
}

int		ft_export(int argc, char **argv, t_environ *environ)
{
	char	*str;
	char	*ptr;
	int		i;
	char	**envstrs;

	if (argc > 1)
		return (apply_export_argv(environ, argv));
	if (list_to_strs_environ(environ, &envstrs) < 0 ||
			!bubble_sort_environ(envstrs, 0, 0))
		return (-1);
	i = 0;
	while (envstrs[i])
	{
		ptr = ft_strlchr(envstrs[i], '=');
		str = ft_strndup(envstrs[i], (ptr - envstrs[i]));
		if (str == NULL)
			exit(-1);
		write_env_export(str, ++ptr, ft_strchr(envstrs[i], '='));
		free(str);
		i++;
	}
	ft_strsfree(envstrs);
	return (0);
}

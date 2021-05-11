/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungwkim <jungwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 01:42:39 by jungwkim          #+#    #+#             */
/*   Updated: 2021/05/11 18:21:46 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "libft.h"

int		realloc_argv(char ***argv, int *idx, int *flag)
{
	char	**new;
	int		i;

	new = (char **)malloc(sizeof(char *) * (ft_strslen(*argv)));
	if (new == NULL)
		return (-1);
	i = -1;
	while (++i < (int)ft_strslen(*argv))
		new[i] = NULL;
	i = -1;
	*flag = 0;
	while ((*argv)[++i])
		if (i == *idx)
			*flag = 1;
		else
		{
			new[i - *flag] = ft_strdup((*argv)[i]);
			if (new[i - *flag] == NULL)
				return (-1);
		}
	ft_strsfree(*argv);
	*argv = new;
	*idx -= 1;
	return (1);
}

int		alloc_env_value(char *key, char ***argv, char **value, int *flag)
{
	char	*ptr;
	char	*arg_key;
	int		i;

	i = -1;
	while ((*argv)[++i])
	{
		ptr = ft_strlchr((*argv)[i], '=');
		arg_key = ft_strndup((*argv)[i], ptr - (*argv)[i]);
		if (!ft_strcmp(arg_key, key))
		{
			*value = ptr + 1;
			if ((ptr + 1 != NULL && *value == NULL) ||
				realloc_argv(argv, &i, flag) < 0)
			{
				free(arg_key);
				return (-1);
			}
		}
		free(arg_key);
	}
	return (1);
}

int		search_env_key(char *key, char ***argv)
{
	char	*value;
	int		flag;

	value = NULL;
	flag = 0;
	if (alloc_env_value(key, argv, &value, &flag) < 0)
		return (-1);
	if (flag && !value)
		write(1, "", 0);
	else if (flag && value)
		write(1, value, ft_strlen(value));
	return (flag);
}

int		write_original_environ(t_environ *environ, char ***argv)
{
	char	*ptr;
	char	*key;
	int		ret;

	while (environ)
	{
		ret = 0;
		ptr = ft_strlchr(environ->env, '=');
		key = ft_strndup(environ->env, ptr - environ->env);
		if (ft_strlchr(environ->env, '='))
		{
			write(1, key, ft_strlen(key));
			write(1, "=", 1);
			if (*argv)
				ret = search_env_key(key, argv);
			if (ret < 0)
				return (-1);
			else if (!ret && ptr + 1)
				write(1, ptr + 1, ft_strlen(ptr + 1));
			write(1, "\n", 1);
		}
		free(key);
		environ = environ->next;
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungwkim <jungwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 01:42:39 by jungwkim          #+#    #+#             */
/*   Updated: 2021/05/09 02:37:17 by jungwkim         ###   ########.fr       */
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
	char	**arg_tmp;
	int		i;

	i = -1;
	while ((*argv)[++i])
	{
		arg_tmp = ft_split((*argv)[i], '=');
		if (arg_tmp == NULL)
			return (-1);
		if (!ft_strcmp(arg_tmp[0], key))
		{
			free(*value);
			*value = ft_strdup(arg_tmp[1]);
			if ((arg_tmp[1] != NULL && *value == NULL) ||
				realloc_argv(argv, &i, flag) < 0)
			{
				ft_strsfree(arg_tmp);
				return (-1);
			}
		}
		ft_strsfree(arg_tmp);
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
	free(value);
	return (flag);
}

int		write_original_environ(t_environ *environ, char ***argv)
{
	char	**env_tmp;
	int		ret;

	while (environ)
	{
		ret = 0;
		env_tmp = ft_split(environ->env, '=');
		if (!env_tmp)
			return (-1);
		if (ft_strchr(environ->env, '='))
		{
			write(1, env_tmp[0], ft_strlen(env_tmp[0]));
			write(1, "=", 1);
			if (*argv)
				ret = search_env_key(env_tmp[0], argv);
			if (ret < 0)
				return (-1);
			else if (!ret && env_tmp[1])
				write(1, env_tmp[1], ft_strlen(env_tmp[1]));
			write(1, "\n", 1);
		}
		ft_strsfree(env_tmp);
		environ = environ->next;
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungwkim <jungwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 03:46:24 by jungwkim          #+#    #+#             */
/*   Updated: 2021/05/02 15:53:54 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "execute/execute.h"
#include "libft.h"

int		create_envset(char ***envset, char *arg, int *flag)
{
	int		i;
	int		j;

	i = count_envset(arg);
	if (arg[ft_strlen(arg) - 1] == '$')
		*flag = 1;
	*envset = (char **)malloc(sizeof(char *) * (i + (*flag) + 1));
	if (*envset == NULL)
		return (0);
	j = -1;
	while (++j < i + *flag)
		(*envset)[j] = NULL;
	(*envset)[j] = NULL;
	return (1);
}

int		init_envset(char **envset, char *arg, int flag)
{
	char	**strs;
	int		num;
	int		i;

	strs = ft_split(arg, '$');
	if (strs == NULL)
		return (0);
	num = count_envset(arg);
	i = -1;
	while (++i < num)
		if (!dup_envset(&envset[i], strs[i]))
		{
			clear_envset(strs);
			clear_envset(envset);
			return (0);
		}
	if (flag && !dup_envset(&envset[i], "$"))
	{
		clear_envset(strs);
		clear_envset(envset);
		return (0);
	}
	envset[i + flag] = NULL;
	clear_envset(strs);
	return (1);
}

int		replace_envset(char **envset, char *arg)
{
	char	*value;
	int		i;
	int		num;

	i = -1;
	if (*arg != '$')
		i = 0;
	num = count_envset(arg);
	while (envset[++i] && i < num)
	{
		value = getenv(envset[i]);
		if (!value && !dup_envset(&envset[i], ""))
		{
			clear_envset(envset);
			return (0);
		}
		else if (value && !dup_envset(&envset[i], value))
		{
			clear_envset(envset);
			return (0);
		}
	}
	return (1);
}

int		join_envset(char **envset, char **arg)
{
	int		i;
	int		len;
	char	*str;

	i = -1;
	len = 0;
	while (envset[++i])
		len += ft_strlen(envset[i]);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
	{
		clear_envset(envset);
		return (0);
	}
	i = -1;
	len = 0;
	while (envset[++i])
	{
		ft_strncpy(str + len, envset[i], ft_strlen(envset[i]));
		len += ft_strlen(envset[i]);
	}
	str[len] = '\0';
	free(*arg);
	*arg = str;
	return (1);
}

int		check_envset(t_pipeline *pipeline)
{
	char		**envset;
	int			i;
	int			j;
	int			flag;

	i = -1;
	while (++i < pipeline->length)
	{
		j = 0;
		while (++j < pipeline->operations[i].argc)
		{
			flag = 0;
			if (!create_envset(&envset, pipeline->operations[i].argv[j], &flag))
				return (0);
			if (!init_envset(envset, pipeline->operations[i].argv[j], flag))
				return (0);
			if (!replace_envset(envset, pipeline->operations[i].argv[j]))
				return (0);
			if (!join_envset(envset, &pipeline->operations[i].argv[j]))
				return (0);
			clear_envset(envset);
		}
	}
	return (1);
}

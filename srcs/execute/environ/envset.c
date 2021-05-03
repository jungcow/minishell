/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungwkim <jungwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 18:21:37 by jungwkim          #+#    #+#             */
/*   Updated: 2021/05/03 21:07:24 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "execute/execute.h"
#include "libft.h"

int		create_envset(char ***envset, char *env, int *flag)
{
	int		i;
	int		j;

	i = count_envset(env);
	if (env[ft_strlen(env) - 1] == '$')
		*flag = 1;
	*envset = (char **)malloc(sizeof(char *) * (i + (*flag) + 1));
	if (*envset == NULL)
		return (-1);
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
		return (-1);
	num = count_envset(arg);
	i = -1;
	while (++i < num)
		if (!dup_envset(&envset[i], strs[i]))
		{
			clear_envset(strs);
			clear_envset(envset);
			return (-1);
		}
	if (flag && !dup_envset(&envset[i], "$"))
	{
		clear_envset(strs);
		clear_envset(envset);
		return (-1);
	}
	envset[i + flag] = NULL;
	clear_envset(strs);
	return (1);
}

int		replace_envset(char **envset, char *arg)
{
	int		i;
	int		num;

	i = -1;
	if (*arg != '$')
		i = 0;
	num = count_envset(arg);
	while (envset[++i] && i < num)
	{
		if (get_envstr(envset, i) < 0)
			return (-1);
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
		return (-1);
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

int		check_envset(char **env)
{
	char	**envset;
	int		flag;
	int		ret;

	flag = 0;
	ret = create_envset(&envset, *env, &flag);
	if (ret >= 0)
		ret = init_envset(envset, *env, flag);
	if (ret >= 0)
		ret = replace_envset(envset, *env);
	if (ret >= 0)
		ret = join_envset(envset, env);
	clear_envset(envset);
	if (ret < 0)
		return (-1);
	return (1);
}

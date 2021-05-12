/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungwkim <jungwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 18:21:37 by jungwkim          #+#    #+#             */
/*   Updated: 2021/05/13 02:49:38 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "execute/execute.h"
#include "libft.h"

int		init_envset(char **envset, char *arg)
{
	int		i;
	int		tmp;
	int		flag;
	int		exit_flag;

	i = 0;
	while (arg[i])
	{
		tmp = i;
		flag = 0;
		exit_flag = 0;
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			flag = arg[i++];
		if (flag == BACKSLASH && arg[i])
			i++;
		else if (flag == '$' && arg[i] == '?' && i++)
			exit_flag = 1;
		while ((ft_isalnum(arg[i]) || arg[i] == '_') && !exit_flag)
			i++;
		*envset = ft_strndup(arg + tmp, i - tmp);
		if (*envset == NULL)
			exit(-1);
		envset++;
	}
	return (1);
}

int		create_envset(char ***envset, char *arg)
{
	int		i;
	int		num;

	i = 0;
	num = count_envset(arg);
	*envset = (char **)malloc(sizeof(char *) * (num + 1));
	i = 0;
	while (i < num)
		(*envset)[i++] = NULL;
	(*envset)[i] = NULL;
	init_envset(*envset, arg);
	return (1);
}

int		replace_envset(char **envset, char *arg)
{
	int		i;
	int		num;

	i = 0;
	num = count_envset(arg);
	while (envset[i])
	{
		if ((envset[i][0] == '$' && envset[i][1]) || envset[i][0] == '\\')
		{
			if (envset[i][0] == BACKSLASH)
				handle_backslash(envset + i);
			else if (envset[i][0] == '$')
				handle_dollar(envset + i);
		}
		i++;
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
		exit(-1);
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
	int		ret;

	if (!(*env) || **env == '\0')
		return (1);
	ret = create_envset(&envset, *env);
	if (ret >= 0)
		ret = replace_envset(envset, *env);
	if (ret >= 0)
		ret = join_envset(envset, env);
	clear_strs(envset);
	if (ret < 0)
		return (-1);
	return (1);
}

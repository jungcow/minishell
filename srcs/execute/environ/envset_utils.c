/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envset_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungwkim <jungwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 03:51:39 by jungwkim          #+#    #+#             */
/*   Updated: 2021/05/04 00:51:26 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "execute/execute.h"
#include "libft.h"

char	*get_alnum_envstr(char *env, char **noalnum)
{
	char	*alnum;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(env);
	while (ft_isalnum(env[i]))
		i++;
	alnum = ft_strndup(env, i);
	if (alnum == NULL)
		return (NULL);
	*noalnum = ft_strndup(env + i, len - i);
	if (*noalnum == NULL)
	{
		free(alnum);
		return (NULL);
	}
	return (alnum);
}

int		get_envstr(char **envset, int idx)
{
	char	*rest;
	char	*env;
	char	*value;

	rest = NULL;
	env = NULL;
	env = get_alnum_envstr(envset[idx], &rest);
	if (env == NULL)
		return (-1);
	value = getenv(env);
	if (!value && !dup_envset(&env, ""))
		return (-1);
	else if (value && !dup_envset(&env, value))
		return (-1);
	free(envset[idx]);
	envset[idx] = ft_strjoin(env, rest);
	if (envset[idx] == NULL)
		return (-1);
	free(env);
	free(rest);
	return (1);
}

int		dup_envset(char **env, char *str)
{
	free(*env);
	*env = ft_strdup(str);
	if (*env == NULL)
		return (0);
	return (1);
}

int		count_envset(char *arg)
{
	int		i;
	int		num;

	i = 0;
	num = 0;
	while (arg[i])
	{
		if (arg[i] == '$' && (arg[i + 1] != '$' && arg[i + 1] != '\0'))
			num++;
		i++;
	}
	if (*arg != '$')
		num++;
	return (num);
}

void	clear_strs(char **envset)
{
	int		i;

	i = 0;
	while (envset[i])
	{
		free(envset[i]);
		i++;
	}
	free(envset);
}

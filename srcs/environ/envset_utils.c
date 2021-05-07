/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envset_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungwkim <jungwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 03:51:39 by jungwkim          #+#    #+#             */
/*   Updated: 2021/05/06 22:25:46 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "command/command.h"
#include "execute/execute.h"
#include "libft.h"

extern t_command	g_command;

int		get_alnum_envstr(char *env, char **alnum, char **noalnum)
{
	int		i;
	int		len;
	int		flag;

	i = 0;
	flag = 1;
	len = ft_strlen(env);
	while (ft_isalnum(env[i]))
		i++;
	if (env[0] == '?')
	{
		i = 1;
		flag = 0;
	}
	*alnum = ft_strndup(env, i);
	if (*alnum == NULL)
		return (-1);
	*noalnum = ft_strndup(env + i, len - i);
	if (*noalnum == NULL)
	{
		free(*alnum);
		return (-1);
	}
	return (flag);
}

int		get_envstr(char **envset, int idx)
{
	char	*rest;
	char	*env;
	char	*value;
	int		flag;

	rest = NULL;
	env = NULL;
	flag = get_alnum_envstr(envset[idx], &env, &rest);
	if (flag == -1)
		return (-1);
	value = getenv(env);
	if (flag == 0 && dup_str(&value, ft_itoa(g_command.prev_exit_status)) < 0)
		return (-1);
	if (!value && dup_str(&env, "") < 0)
		return (-1);
	else if (value && dup_str(&env, value) < 0)
		return (-1);
	free(envset[idx]);
	envset[idx] = ft_strjoin(env, rest);
	if (envset[idx] == NULL)
		return (-1);
	free(env);
	free(rest);
	return (1);
}

int		dup_str(char **env, char *str)
{
	free(*env);
	*env = ft_strdup(str);
	if (*env == NULL)
		return (-1);
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

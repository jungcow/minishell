/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envset_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungwkim <jungwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 03:51:39 by jungwkim          #+#    #+#             */
/*   Updated: 2021/05/13 02:43:35 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "command/command.h"
#include "execute/execute.h"
#include "libft.h"

extern t_command	g_command;

int		handle_backslash(char **envset)
{
	const char	*set = "$\\\"`";
	char		*tmp;

	if (ft_strchr(set, (*envset)[1]))
	{
		tmp = ft_strdup(*envset + 1);
		if (tmp == NULL)
			exit(-1);
		free(*envset);
		*envset = tmp;
	}
	return (1);
}

int		handle_dollar(char **envset)
{
	char		*tmp;

	if ((*envset)[1] == '?')
	{
		free(*envset);
		*envset = ft_itoa(g_command.prev_exit_status);
		return (1);
	}
	tmp = get_environ(*envset + 1);
	if (tmp == NULL)
	{
		tmp = ft_strdup("");
		if (tmp == NULL)
			exit(-1);
	}
	free(*envset);
	*envset = tmp;
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
	int		flag;

	flag = 0;
	i = 0;
	if (!ft_isalnum(arg[i]) && arg[i] != '_')
		flag = arg[i++];
	if (flag == BACKSLASH)
		i++;
	num = 1;
	while (arg[i])
	{
		flag = 0;
		if ((!ft_isalnum(arg[i]) && arg[i] != '_'))
			flag = arg[i];
		if (flag == BACKSLASH && arg[i + 1])
			i++;
		else if (flag == '$' && arg[i + 1] == '?')
			i++;
		if (flag)
			num++;
		i++;
	}
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

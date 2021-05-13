/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envset_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungwkim <jungwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 03:51:39 by jungwkim          #+#    #+#             */
/*   Updated: 2021/05/13 15:39:05 by jungwkim         ###   ########.fr       */
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
	int			i;

	i = 1;
	if ((*envset)[0] == BACKSLASH)
		i++;
	if ((*envset)[i] == '?')
		tmp = ft_itoa(g_command.prev_exit_status);
	else
	{
		tmp = get_environ(*envset + i);
		if (tmp == NULL)
			tmp = ft_strdup("");
	}
	if (tmp == NULL)
		exit(-1);
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

int		count_envset(char *arg, int flag)
{
	int		i;
	int		num;
	int		tmp;

	i = 0;
	tmp = 0;
	if (!ft_isalnum(arg[i]) && arg[i] != '_')
		tmp = arg[i++];
	if (flag == DOUBLE_QUOTE && tmp == BACKSLASH)
		i++;
	num = 1;
	while (arg[i])
	{
		tmp = 0;
		if ((!ft_isalnum(arg[i]) && arg[i] != '_'))
			tmp = arg[i];
		if (flag == DOUBLE_QUOTE && tmp == BACKSLASH && arg[i + 1])
			i++;
		else if (tmp == '$' && arg[i + 1] == '?')
			i++;
		if (tmp)
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

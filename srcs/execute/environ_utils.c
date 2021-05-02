/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungwkim <jungwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 03:51:39 by jungwkim          #+#    #+#             */
/*   Updated: 2021/05/02 22:01:39 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "execute/execute.h"
#include "libft.h"

void	clear_envset(char **envset)
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

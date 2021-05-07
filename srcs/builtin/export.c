/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungwkim <jungwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 12:24:21 by jungwkim          #+#    #+#             */
/*   Updated: 2021/05/07 13:20:24 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>
#include "libft.h"
#include "builtin.h"

int		bubble_sort(char **env)
{
	int		i;
	int		j;
	char	*tmp;

	j = ft_strslen(env) - 1;
	while (j--)
	{
		i = -1;
		while (env[++i])
			if (env[i + 1] != NULL)
				if (ft_strcmp(env[i], env[i + 1]) > 0)
				{
					tmp = ft_strdup(env[i]);
					free(env[i]);
					env[i] = ft_strdup(env[i + 1]);
					if (tmp == NULL || env[i] == NULL)
						return (0);
					free(env[i + 1]);
					env[i + 1] = tmp;
				}
	}
	return (1);
}

int		ft_export(int argc, char **argv, char **env)
{
	int		i;

	i = 0;
	if (argc == 2)
	{
		bubble_sort(env);
		while (env[i])
		{
			write(1, "declare -x ", ft_strlen("declare -x "));
			write(1, env[i], ft_strlen(env[i]));
			write(1, "\n", 1);
			i++;
		}
		return (errno);
	}
	
	return (errno);
}

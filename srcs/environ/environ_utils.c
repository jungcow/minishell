/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungwkim <jungwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 17:31:13 by jungwkim          #+#    #+#             */
/*   Updated: 2021/05/08 17:40:56 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ/environ.h"
#include "libft.h"

int		bubble_sort_environ(char **envstrs)
{
	int			j;
	int			i;

	j = ft_strslen(envstrs);
	while (--j)
	{
		i = 0;
		while (envstrs[i + 1])
		{
			if (ft_strcmp(envstrs[i], envstrs[i + 1]) > 0)
				if (!ft_strswap(&envstrs[i], &envstrs[i + 1]))
					return (0);
			i++;
		}
	}
	return (1);
}

int		list_to_strs_environ(t_environ *environ, char ***env)
{
	t_environ	*tmp;
	int			len;
	int			i;

	len = 0;
	tmp = environ;
	while (tmp && ++len)
		tmp = tmp->next;
	*env = (char **)malloc(sizeof(char *) * (++len));
	if (*env == NULL)
		return (-1);
	while (len)
		(*env)[--len] = NULL;
	i = 0;
	while (environ && ++i)
	{
		(*env)[i - 1] = ft_strdup(environ->env);
		if ((*env)[i - 1] == NULL)
		{
			ft_strsfree(*env);
			return (-1);
		}
		environ = environ->next;
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungwkim <jungwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 12:24:21 by jungwkim          #+#    #+#             */
/*   Updated: 2021/05/07 19:58:17 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>
#include "libft.h"
#include "builtin.h"

/*
int		bubble_sort(t_environ *environ)
{
	int		i;
	int		j;
	char	*tmp;

	
	while (j--)
	{
		i = -1;
		while (environ->next)
			if (environ->next != NULL)
				if (ft_strcmp(environ, environ->next) > 0)
				{
					tmp = ft_strdup(environ);
					free(environ);
					environ = ft_strdup(environ->next);
					if (tmp == NULL || environ == NULL)
						return (0);
					free(environ->next);
					environ->next = tmp;
				}
	}
	return (1);
}

int		ft_export(int argc, char **argv, t_environ *environ)
{
	int		i;

	i = 0;
	if (argc == 2)
	{
		bubble_sort(environ);
		while (environ)
		{
			write(1, "declare -x ", ft_strlen("declare -x "));
			write(1, environ->env, ft_strlen(environ->env));
			write(1, "\n", 1);
			environ = environ->next;
		}
		return (errno);
	}
	
	return (errno);
}
*/

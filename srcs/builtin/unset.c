/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungwkim <jungwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 18:04:05 by jungwkim          #+#    #+#             */
/*   Updated: 2021/05/10 19:01:35 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "libft.h"

int		search_key_unset(t_environ *environ, char *arg)
{
	char	**strs;
	char	*key;
	int		i;

	i = 1;
	while (environ)
	{
		strs = ft_split(environ->env, '=');
		if (strs == NULL)
			return (-1);
		key = strs[0];
		if (ft_strcmp(arg, key) == 0)
		{
			ft_strsfree(strs);
			return (i);
		}
		ft_strsfree(strs);
		environ = environ->next;
		i++;
	}
	return (0);
}

int		ft_unset(int argc, char **argv, t_environ **environ)
{
	int		i;
	int		ret;

	if (argc == 1)
		return (0);
	i = 1;
	while (i < argc)
	{
		ret = search_key_unset(*environ, argv[i]);
		if (ret < 0)
			return (-1);
		else if (ret > 0)
			dealloc_environ(environ, ret);
		i++;
	}
	return (0);
}

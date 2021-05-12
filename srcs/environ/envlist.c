/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlist.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungwkim <jungwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 18:12:44 by jungwkim          #+#    #+#             */
/*   Updated: 2021/05/13 02:33:12 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "execute/execute.h"
#include "libft.h"

int		create_envlist(t_envlist **envlist)
{
	*envlist = (t_envlist *)malloc(sizeof(t_envlist));
	if (*envlist == NULL)
		return (-1);
	(*envlist)->env = NULL;
	(*envlist)->flag = 0;
	(*envlist)->next = NULL;
	return (1);
}

int		init_envlist(t_envlist **envlist, char *arg)
{
	t_envlist	*new;
	int			i;
	int			tmp;
	int			num;

	i = 0;
	while (arg[i])
	{
		if (create_envlist(&new) == -1)
			return (-1);
		tmp = i;
		num = count_envstr(arg, &i, &new->flag);
		if (new->flag == SINGLE_QUOTE || new->flag == DOUBLE_QUOTE)
			tmp++;
		new->env = ft_strndup(&arg[tmp], num);
		if (new->env == NULL)
			return (-1);
		add_envlist_back(envlist, new);
		i++;
	}
	return (1);
}

int		prepare_envlist(t_envlist **envlist, char *arg)
{
	*envlist = NULL;
	if (init_envlist(envlist, arg) < 0)
		return (-1);
	return (1);
}

int		replace_envlist(t_envlist *envlist)
{
	while (envlist)
	{
		if (envlist->flag == DOUBLE_QUOTE || envlist->flag == NONE_QUOTE)
			if (check_envset(&envlist->env) < 0)
				return (-1);
		envlist = envlist->next;
	}
	return (1);
}

int		join_envlist(t_envlist *envlist, char **arg)
{
	t_envlist	*ptr;
	int			len;
	char		*str;

	ptr = envlist;
	len = 0;
	while (ptr)
	{
		len += ft_strlen(ptr->env);
		ptr = ptr->next;
	}
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (-1);
	len = 0;
	while (envlist)
	{
		ft_strncpy(str + len, envlist->env, ft_strlen(envlist->env));
		len += ft_strlen(envlist->env);
		envlist = envlist->next;
	}
	str[len] = '\0';
	free(*arg);
	*arg = str;
	return (1);
}

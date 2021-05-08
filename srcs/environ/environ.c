/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungwkim <jungwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 03:46:24 by jungwkim          #+#    #+#             */
/*   Updated: 2021/05/08 16:33:12 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "execute/execute.h"

int		init_environ(t_environ **environ, char **env)
{
	int		len;
	int		i;

	len = ft_strslen(env);
	*environ = (t_environ *)malloc(sizeof(t_environ) * len);
	if (*environ == NULL)
		return (0);
	*environ = NULL;
	i = 0;
	while (i < len)
	{
		if (!alloc_environ(environ, env[i]))
		{
			clear_environ(*environ);
			return (0);
		}
		i++;
	}
	return (1);
}

int		alloc_environ(t_environ **environ, char *env)
{
	t_environ	*new;
	t_environ	*tmp;

	new = (t_environ *)malloc(sizeof(t_environ));
	if (new == NULL)
		return (0);
	new->env = ft_strdup(env);
	if (new->env == NULL)
		return (0);
	new->next = NULL;
	if (*environ == NULL)
		*environ = new;
	else
	{
		tmp = *environ;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (1);
}

/*
int		dealloc_environ(t_environ **head, char **argv)
{
	t_environ	*ptr;
	t_environ	*tmp;

	ptr = *head;
	if (ft_strcmp(ptr->env, *argv) == 0)
	{
		*head = (*head)->next;
		ptr->next = NULL;
		clear_environ(ptr);
	}
	ptr = *head;
	while (ptr && *argv)
	{
		if (ft_strcmp(ptr->env, *argv) == 0 || ft_strcmp(ptr->env, *argv) == 0)
		{
			tmp->next = ptr->next;
			argv++;
		}
		tmp = ptr;
		ptr = ptr->next;
	}
}
*/

int		check_environ(t_pipeline *pipeline)
{
	t_envlist	*envlist;
	int			i;
	int			j;
	int			ret;

	i = -1;
	while (++i < pipeline->length)
	{
		j = -1;
		while (++j < pipeline->operations[i].argc)
		{
			envlist = NULL;
			ret = prepare_envlist(&envlist, pipeline->operations[i].argv[j]);
			if (ret >= 0)
				ret = replace_envlist(envlist);
			if (ret >= 0)
				ret = join_envlist(envlist, &pipeline->operations[i].argv[j]);
			clear_envlist(envlist);
			if (ret < 0)
				return (-1);
		}
	}
	return (1);
}

void	clear_environ(t_environ *environ)
{
	t_environ	*tmp;

	while (environ)
	{
		tmp = environ;
		free(tmp->env);
		tmp->env = NULL;
		tmp->next = NULL;
		free(tmp);
		environ = environ->next;
	}
}

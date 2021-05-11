/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungwkim <jungwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 17:31:13 by jungwkim          #+#    #+#             */
/*   Updated: 2021/05/11 18:26:54 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ/environ.h"
#include "command/command.h"
#include "libft.h"

extern t_command	g_command;

char	*get_environ(char *env)
{
	t_environ	*environ;
	char		*ptr;
	char		*key;
	char		*ret;

	environ = g_command.environ;
	while (environ)
	{
		ptr = ft_strlchr(environ->env, '=');
		key = ft_strndup(environ->env, ptr - environ->env);
		if (!key)
			exit(-1);
		if (ft_strcmp(key, env) == 0)
		{
			if (ptr + 1 == NULL)
				ret = ft_strdup("");
			else
				ret = ft_strdup(ptr + 1);
			free(key);
			return (ret);
		}
		free(key);
		environ = environ->next;
	}
	return (NULL);
}

int		bubble_sort_environ(char **envstrs, int i, int j)
{
	char		*key1;
	char		*key2;
	char		*ptr;

	j = ft_strslen(envstrs);
	while (--j)
	{
		i = -1;
		while (envstrs[++i + 1])
		{
			ptr = ft_strlchr(envstrs[i], '=');
			key1 = ft_strndup(envstrs[i], ptr - envstrs[i]);
			ptr = ft_strlchr(envstrs[i + 1], '=');
			key2 = ft_strndup(envstrs[i + 1], ptr - envstrs[i + 1]);
			if (!key1 || !key2)
				exit(-1);
			if (ft_strcmp(key1, key2) > 0)
				if (!ft_strswap(&envstrs[i], &envstrs[i + 1]))
					return (0);
			free(key1);
			free(key2);
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

void	dealloc_environ_head(t_environ **head)
{
	t_environ	*tmp;

	tmp = *head;
	*head = (*head)->next;
	free(tmp->env);
	tmp->next = NULL;
	free(tmp);
	tmp = NULL;
}

void	dealloc_environ_nohead(t_environ *prev, t_environ *tmp)
{
	if (tmp->next == NULL)
	{
		prev->next = NULL;
		clear_environ(tmp);
	}
	else
	{
		prev->next = tmp->next;
		tmp->next = NULL;
		clear_environ(tmp);
	}
}

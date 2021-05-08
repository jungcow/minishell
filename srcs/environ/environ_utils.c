/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungwkim <jungwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 17:31:13 by jungwkim          #+#    #+#             */
/*   Updated: 2021/05/08 21:18:29 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environ/environ.h"
#include "command/command.h"
#include "libft.h"

extern t_command	g_command;

char	*get_environ(char *env)
{
	t_environ	*environ;
	char		**strs;
	char		*ret;

	environ = g_command.environ;
	while (environ)
	{
		strs = ft_split(environ->env, '=');
		if (strs == NULL)
			return (NULL);
		if (ft_strcmp(strs[0], env) == 0)
		{
			if (strs[1] == NULL)
				ret = ft_strdup("");
			else
				ret = ft_strdup(strs[1]);
			ft_strsfree(strs);
			return (ret);
		}
		ft_strsfree(strs);
		environ = environ->next;
	}
	return (NULL);
}

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

void	dealloc_environ_head(t_environ **head)
{
	t_environ	*tmp;

	tmp = *head;
	*head = (*head)->next;
	tmp->next = NULL;
	clear_environ(tmp);
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

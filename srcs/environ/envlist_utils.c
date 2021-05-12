/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlist_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungwkim <jungwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 18:14:12 by jungwkim          #+#    #+#             */
/*   Updated: 2021/05/13 02:32:33 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute/execute.h"

void		clear_envlist(t_envlist *envlist)
{
	t_envlist	*tmp;

	while (envlist)
	{
		tmp = envlist;
		envlist = envlist->next;
		free(tmp->env);
		tmp->next = NULL;
		tmp->env = NULL;
		free(tmp);
	}
}

int			count_envstr(char *arg, int *idx, int *flag)
{
	int		num;
	int		backslash;

	if (arg[*idx] == SINGLE_QUOTE || arg[*idx] == DOUBLE_QUOTE)
		*flag = arg[(*idx)++];
	else
		*flag = NONE_QUOTE;
	num = 0;
	backslash = 0;
	while (arg[*idx] && ((*flag == SINGLE_QUOTE && (arg[*idx] != SINGLE_QUOTE))
		|| (*flag == DOUBLE_QUOTE && (arg[*idx] != DOUBLE_QUOTE || backslash))
		|| (*flag == NONE_QUOTE
		&& (arg[*idx] != SINGLE_QUOTE && arg[*idx] != DOUBLE_QUOTE))))
	{
		num++;
		if (arg[*idx] == BACKSLASH && !backslash)
			backslash = 1;
		else
			backslash = 0;
		(*idx)++;
	}
	if (*flag == NONE_QUOTE)
		(*idx)--;
	return (num);
}

t_envlist	*move_envlist_last(t_envlist *envlist)
{
	while (envlist->next)
		envlist = envlist->next;
	return (envlist);
}

void		add_envlist_back(t_envlist **envlist, t_envlist *new)
{
	t_envlist	*last;

	if (*envlist == NULL)
		*envlist = new;
	else
	{
		last = move_envlist_last(*envlist);
		last->next = new;
	}
}

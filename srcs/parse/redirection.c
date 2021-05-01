/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoh <seunghoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 15:43:22 by seunghoh          #+#    #+#             */
/*   Updated: 2021/05/01 19:01:12 by seunghoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include "libft.h"
#include "parse/parse_util.h"
#include "parse/operation.h"

bool		create_redirection(t_operation *operation, int count)
{
	int		i;

	if (count == 0)
		return (true);
	operation->redirects = (t_redirect *)malloc(sizeof(t_redirect) * count);
	if (operation->redirects == NULL)
		return (false);
	operation->len_redirects = count;
	i = 0;
	while (i < count)
		operation->redirects[i++].to = NULL;
	return (true);
}

int			count_redirection(char *token)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (token[i] != '\0')
	{
		if (token[i] == 34)
			i = skip_quote(token, ft_strlen(token), i);
		else if (token[i] == 39)
			i = skip_dquote(token, ft_strlen(token), i);
		else if (token[i] == '<')
			count++;
		else if (token[i] == '>' && token[i + 1] == '>')
		{
			count++;
			i++;
		}
		else if (token[i] == '>')
			count++;
		i++;
	}
	return (count);
}

void		parse_redirection(t_redirect *redirect, char *token)
{
	int	i;
	int	count;
	int	len;

	i = 0;
	count = 0;
	len = ft_strlen(token);
	(void)redirect;
	while (token[i] != '\0')
	{
		if (token[i] == 34)
			i = skip_quote(token, len, i);
		else if (token[i] == 39)
			i = skip_dquote(token, len, i);
		i++;
	}
}

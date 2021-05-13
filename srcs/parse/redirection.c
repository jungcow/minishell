/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoh <seunghoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 15:43:22 by seunghoh          #+#    #+#             */
/*   Updated: 2021/05/13 17:56:28 by seunghoh         ###   ########.fr       */
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
	{
		operation->redirects[i].to = NULL;
		operation->redirects[i].is_append = false;
		i++;
	}
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
		if (token[i] == 39)
			i = skip_quote(token, ft_strlen(token), i);
		else if (token[i] == 34)
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

void		parse_redirect_from(t_redirect *redirect, char *token, int *i)
{
	if (token[*i] == '<')
		redirect->from = 0;
	else
		redirect->from = 1;
	token[*i] = ' ';
	redirect->is_append = false;
	if (token[*i + 1] == '>')
	{
		token[*i + 1] = ' ';
		redirect->is_append = true;
	}
	while (token[*i] != '\0')
	{
		if (token[*i] != ' ' && token[*i] != '\n')
			break ;
		*i += 1;
	}
}

bool		parse_redirect_to(t_redirect *redirect, char *token, int *i)
{
	int		start;
	char	dump;

	start = *i;
	while (token[*i] != '\0')
	{
		if (ft_strchr("<> \n", token[*i]) != NULL)
			break ;
		else if (token[*i] == 39)
			*i = skip_quote(token, ft_strlen(token), *i);
		else if (token[*i] == 34)
			*i = skip_dquote(token, ft_strlen(token), *i);
		*i += 1;
	}
	dump = token[*i];
	token[*i] = '\0';
	redirect->to = ft_strdup(token + start);
	token[*i] = dump;
	while (start < *i)
		token[start++] = ' ';
	if (redirect->to == NULL)
		return (false);
	*i -= 1;
	return (true);
}

bool		parse_redirection(t_redirect *redirect, char *token)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (token[i] != '\0')
	{
		if (token[i] == 39)
			i = skip_quote(token, ft_strlen(token), i);
		else if (token[i] == 34)
			i = skip_dquote(token, ft_strlen(token), i);
		else if (token[i] == '<' || token[i] == '>')
		{
			parse_redirect_from(&redirect[count], token, &i);
			if (!parse_redirect_to(&redirect[count++], token, &i))
				return (false);
		}
		i++;
	}
	return (true);
}

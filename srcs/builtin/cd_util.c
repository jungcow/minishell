/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_util.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoh <seunghoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 14:44:43 by seunghoh          #+#    #+#             */
/*   Updated: 2021/05/11 16:27:45 by seunghoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include "command/command.h"
#include "execute/execute.h"
#include "error/error.h"
#include "environ/environ.h"

extern t_command	g_command;

t_environ	*get_pwd_env(char *token)
{
	t_environ	*environ;

	environ = g_command.environ;
	while (environ)
	{
		if (ft_strcmp(environ->env, token) == '=')
			return (environ);
		environ = environ->next;
	}
	return (NULL);
}

void		make_pwd(char *token)
{
	t_environ	*env;
	char		*old_pwd;
	char		*new_pwd;

	env = get_pwd_env(token);
	if (env == NULL)
		return ;
	old_pwd = ft_strjoin(token, "=");
	if (old_pwd == NULL)
		exit(1);
	new_pwd = ft_strjoin(old_pwd, g_command.pwd);
	free(old_pwd);
	if (new_pwd == NULL)
		exit(1);
	free(env->env);
	env->env = new_pwd;
}

void		update_pwd(char **argv)
{
	char	*pwd;

	make_pwd("OLDPWD");
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		fail_getcwd(argv);
	else
		success_getcwd();
	free(argv[1]);
	argv[1] = NULL;
	free(pwd);
	make_pwd("PWD");
}

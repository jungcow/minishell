/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungwkim <jungwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 04:23:28 by jungwkim          #+#    #+#             */
/*   Updated: 2021/05/16 01:34:55 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute/execute.h"
#include "environ/environ.h"
#include "command/command.h"
#include "builtin.h"
#include "libft.h"

extern t_command	g_command;

int		is_builtin(char *command)
{
	char	*builtin[9];
	int		i;

	builtin[0] = "echo";
	builtin[1] = "cd";
	builtin[2] = "pwd";
	builtin[3] = "export";
	builtin[4] = "unset";
	builtin[5] = "env";
	builtin[6] = "exit";
	builtin[7] = "history";
	builtin[8] = NULL;
	i = 0;
	while (builtin[i])
	{
		if (ft_strcmp(command, builtin[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int		ft_execve(char *command, char **argv, t_environ **environ)
{
	int		ret;

	ret = 0;
	if (ft_strcmp(command, "echo") == 0)
	{
		printf("arg: %s\n", argv[1]);
		ret = ft_echo(ft_strslen(argv), argv, *environ);
	}
	else if (ft_strcmp(command, "cd") == 0)
		ret = ft_cd(ft_strslen(argv), argv);
	else if (ft_strcmp(command, "pwd") == 0)
		ret = ft_pwd();
	else if (ft_strcmp(command, "env") == 0)
		ret = ft_env(ft_strslen(argv), argv, *environ);
	else if (ft_strcmp(command, "export") == 0)
		ret = ft_export(ft_strslen(argv), argv, *environ);
	else if (ft_strcmp(command, "unset") == 0)
		ret = ft_unset(ft_strslen(argv), argv, environ);
	else if (ft_strcmp(command, "exit") == 0)
		ret = ft_exit(ft_strslen(argv), argv);
	else if (ft_strcmp(command, "history") == 0)
		ret = ft_history();
	g_command.exit_status = ret;
	if (ret < 0)
		exit(1);
	return (ret);
}

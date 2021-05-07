/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoh <seunghoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 18:33:25 by seunghoh          #+#    #+#             */
/*   Updated: 2021/05/07 22:00:24 by seunghoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include "error/error.h"
#include "execute/execute.h"
#include "command/command.h"

extern t_command	g_command;

int		cd_home(char **argv)
{
	argv[1] = getenv("HOME");
	if (argv[1] == NULL)
	{
		write(2, ERR_HEAD, ft_strlen(ERR_HEAD));
		write(2, CD_ERR, ft_strlen(CD_ERR));
		write(2, CD_HOME_ERR, ft_strlen(CD_HOME_ERR));
		write(2, "\n", 1);
		return(1);
	}
	return (0);
}

void	success_getcwd(void)
{
	free(g_command.pwd);
	g_command.pwd = getcwd(NULL, 0);
	if (g_command.pwd == NULL)
		exit(errno);
}

void	fail_getcwd(char **argv)
{
	char	*temp;

	write(2, CD_ERR, ft_strlen(CD_ERR));
	write(2, CD_CWD_ERR, ft_strlen(CD_CWD_ERR));
	write(2, "\n", 1);
	temp = g_command.pwd;
	if (ft_strcmp(g_command.pwd, "/"))
	{
		temp = ft_strjoin(g_command.pwd, "/");
		if (temp == NULL)
			exit(errno);
		free(g_command.pwd);
	}
	g_command.pwd = ft_strjoin(temp, argv[1]);
	if (g_command.pwd == NULL)
		exit(errno);
	free(temp);
}

int		ft_cd(int argc, char **argv)
{

	if (argc == 1 && cd_home(argv))
		return (1);
	if (chdir(argv[1]) == -1)
	{
		write(2, ERR_HEAD, ft_strlen(ERR_HEAD));
		write(2, CD_ERR, ft_strlen(CD_ERR));
		write(2, argv[1], ft_strlen(argv[1]));
		write(2, NO_SUCH_ERR, ft_strlen(NO_SUCH_ERR));
		write(2, "\n", 1);
		return (1);
	}
	else
	{
		if (getcwd(NULL, 0) == NULL)
			fail_getcwd(argv);
		else
			success_getcwd();
	}
	return (0);
}

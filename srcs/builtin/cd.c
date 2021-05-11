/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoh <seunghoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 18:33:25 by seunghoh          #+#    #+#             */
/*   Updated: 2021/05/11 16:27:13 by seunghoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include "error/error.h"
#include "execute/execute.h"
#include "command/command.h"

extern t_command	g_command;

void	success_getcwd(void)
{
	free(g_command.pwd);
	g_command.pwd = getcwd(NULL, 0);
	if (g_command.pwd == NULL)
		exit(errno);
}

void	delete_slash(char *argv)
{
	int	length;

	if (argv == NULL)
		return ;
	length = ft_strlen(argv);
	while (--length >= 0)
		if (argv[length] == '/')
			argv[length] = '\0';
		else
			break ;
}

void	fail_getcwd(char **argv)
{
	char	*temp;

	write(2, CD_ERR, ft_strlen(CD_ERR));
	write(2, CD_CWD_ERR1, ft_strlen(CD_CWD_ERR1));
	write(2, CD_CWD_ERR2, ft_strlen(CD_CWD_ERR2));
	write(2, NO_SUCH_ERR, ft_strlen(NO_SUCH_ERR));
	write(2, "\n", 1);
	temp = g_command.pwd;
	if (ft_strcmp(g_command.pwd, "/"))
	{
		temp = ft_strjoin(g_command.pwd, "/");
		if (temp == NULL)
			exit(errno);
		free(g_command.pwd);
	}
	delete_slash(argv[1]);
	g_command.pwd = ft_strjoin(temp, argv[1]);
	if (g_command.pwd == NULL)
		exit(errno);
	free(temp);
}

int		cd_home(char **argv)
{
	argv[1] = get_environ("HOME");
	if (argv[1] == NULL)
	{
		write(2, ERR_HEAD, ft_strlen(ERR_HEAD));
		write(2, CD_ERR, ft_strlen(CD_ERR));
		write(2, CD_HOME_ERR, ft_strlen(CD_HOME_ERR));
		write(2, "\n", 1);
		return (1);
	}
	return (0);
}

int		ft_cd(int argc, char **argv)
{
	if (argc == 1 && cd_home(argv))
		return (1);
	argc = chdir(argv[1]);
	if (argc == -1)
	{
		write(2, ERR_HEAD, ft_strlen(ERR_HEAD));
		write(2, CD_ERR, ft_strlen(CD_ERR));
		write(2, argv[1], ft_strlen(argv[1]));
		write(2, NO_SUCH_ERR, ft_strlen(NO_SUCH_ERR));
		write(2, "\n", 1);
		free(argv[1]);
		argv[1] = NULL;
		return (1);
	}
	update_pwd(argv);
	return (0);
}

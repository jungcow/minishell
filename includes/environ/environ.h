/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungwkim <jungwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 17:39:05 by jungwkim          #+#    #+#             */
/*   Updated: 2021/05/07 22:32:53 by seunghoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRON_H
# define ENVIRON_H

# define SINGLE_QUOTE	39
# define DOUBLE_QUOTE	34
# define NONE_QUOTE		0

typedef struct			s_environ
{
	char				*env;
	struct s_environ	*next;
}						t_environ;

typedef struct			s_envlist
{
	char				*env;
	int					flag;
	struct s_envlist	*next;
}						t_envlist;

/*
**		environ
*/
int						init_environ(t_environ **environ, char **env);
int						alloc_environ(t_environ **environ, char *env);
int						dealloc_environ(t_environ *environ, char **argv);
void					clear_environ(t_environ *environ);

/*
**		envlist
*/
int						prepare_envlist(t_envlist **envlist, char *arg);
int						init_envlist(t_envlist **envlist, char *arg);
int						create_envlist(t_envlist **envlist);
int						replace_envlist(t_envlist *envlist);
int						join_envlist(t_envlist *envlist, char **arg);

/*
**		envlist_utils
*/
void					clear_envlist(t_envlist *envlist);
int						count_envstr(char *arg, int *idx, int *flag);
t_envlist				*move_envlist_last(t_envlist *envlist);
void					add_envlist_back(t_envlist **envlist, t_envlist *new);

/*
**		envset
*/
int						check_envset(char **env);
int						create_envset(char ***envset, char *arg, int *flag);
int						init_envset(char **envset, char *arg, int flag);
int						replace_envset(char **envset, char *arg);
int						join_envset(char **envset, char **arg);

/*
**		envset_utils
*/
int						get_alnum_envstr(char *env, char **alnum,
										char **noalnum);
int						get_envstr(char **envset, int idx);
int						count_envset(char *arg);

#endif

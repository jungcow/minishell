/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungwkim <jungwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 15:47:30 by jungwkim          #+#    #+#             */
/*   Updated: 2021/05/02 17:15:13 by seunghoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# define READ 0
# define WRITE 1

# define NO_PIPE 0
# define HAVE_PIPE 1

# include "parse/instruction.h"
# include "execute/process.h"
# include "environ.h"

char	**g_environ;

int		execute_instruction(t_instruction *instruction);

/*
**		process
*/
int		execute_process(pid_t *process, t_pipeline *pipelines);
int		execute_child_process(t_pipeline *pipelines,
							int *new_fd, int *old_fd, int idx);

/*
**		environ
*/
int		check_envset(t_pipeline *pipelines);

/*
**		path
*/
char	*get_path(t_operation *operation);

#endif

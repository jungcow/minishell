/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungwkim <jungwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 15:47:30 by jungwkim          #+#    #+#             */
/*   Updated: 2021/05/01 07:17:19 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# define READ 0
# define WRITE 1

# define NO_PIPE 0
# define HAVE_PIPE 1

# include "parse/instruction.h"
# include "execute/execute_utils.h"

int		execute_instruction(t_instruction *instruction);

int		execute_process(pid_t *process, t_pipeline *pipelines);
int		execute_child_process(t_pipeline *pipelines,
							int *new_fd, int *old_fd, int idx);
int		create_process(pid_t **process, int num);
int		wait_process(pid_t *process, int num);
void	clear_process(pid_t **process);

char	*get_path(t_operation *operation);

#endif

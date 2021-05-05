/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungwkim <jungwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 04:18:05 by jungwkim          #+#    #+#             */
/*   Updated: 2021/05/06 03:32:55 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_H
# define PROCESS_H

# define DIRECTORY 040000
# define PERMISSION 80
# define NO_SUCH 78

int		create_process(pid_t **process, int num);
int		wait_process(pid_t *process, int num);
void	clear_process(pid_t **process);

/*
**		utils
*/
int		check_path_validation(char *command);
int		has_file(char *path, char *filename);
void	close_fds(int *fd);

#endif

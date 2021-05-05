/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungwkim <jungwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 04:18:05 by jungwkim          #+#    #+#             */
/*   Updated: 2021/05/06 04:44:31 by jungwkim         ###   ########.fr       */
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
**		builtin
*/
int		ft_execve(char *command, char **argv, char **env);
int		is_builtin(char *command);

/*
**		utils
*/
int		check_path_validation(char *command);
int		has_file(char *path, char *filename);
void	close_fds(int *fd);

#endif

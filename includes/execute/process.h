/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungwkim <jungwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 04:18:05 by jungwkim          #+#    #+#             */
/*   Updated: 2021/05/02 04:25:06 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_H
# define PROCESS_H

# include <unistd.h>

int		create_process(pid_t **process, int num);
int		wait_process(pid_t *process, int num);
void	clear_process(pid_t **process);

char	*parse_path(char *filename);
int		check_parse_necessary(char *filename);
int		has_file(char * path, char *filename);
void	close_fds(int *fd);

#endif

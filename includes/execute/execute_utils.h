/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungwkim <jungwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 07:00:25 by jungwkim          #+#    #+#             */
/*   Updated: 2021/05/01 07:16:39 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_UTILS_H
# define EXECUTE_UTILS_H

# include "libft.h"

char	*parse_path(char *filename);
int		check_parse_necessary(char *filename);
int		has_file(char * path, char *filename);
void	close_fds(int *fd);

#endif

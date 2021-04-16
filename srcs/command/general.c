/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoh <seunghoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 16:10:56 by seunghoh          #+#    #+#             */
/*   Updated: 2021/04/16 17:01:13 by seunghoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "command/command.h"

int		apply_general_key(t_command *command, int key)
{
	if (key >= 32 &&
		key <= 127)
	{
		if (!add_string(&command->line, command->line.length, key))
			return (-1);
		command->cursor++;
		command->length++;
		write(1, &key, 1);
	}
	return (1);
}

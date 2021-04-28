/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seunghoh <seunghoh@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 18:26:26 by seunghoh          #+#    #+#             */
/*   Updated: 2021/04/28 19:08:50 by seunghoh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse/instruction.h"

void	init_instruction(t_instruction *instruction)
{
	/*
    if (!validate_command(command))
        return (0);
    tokens = split_command(&command->line);
    if (tokens == NULL)
        return (-1);
    i = -1;
    while (tokens[++i] != NULL)
    {
        init_pipeline(&pipeline);
        if (parse_pipeline(tokens[i]) == -1)
            break ;
        // run pipeline
        clear_pipeline(&pipeline);
    }
    clear_tokens(tokens);
	*/
	(void)instruction;
}

int		parse_instruction(t_instruction *instruction, t_string *command)
{
	(void)instruction;
	(void)command;
	return (1);
}

void	clear_instruction(t_instruction *instruction)
{
	(void)instruction;
}

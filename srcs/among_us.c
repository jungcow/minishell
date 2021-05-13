/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   among_us.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungwkim <jungwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 05:19:34 by jungwkim          #+#    #+#             */
/*   Updated: 2021/05/13 14:22:40 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "terminal.h"

void	print_description(void)
{
	printf("Welcome to Imposter shell!\n");
	printf("This program is for 42Seoul minishell subject made by seunghoh\n");
	printf("and jungwkim. The action of this program follow the bash shell.\n");
	printf("If you encounter errors or need other inquiries, welcome slack\n");
	printf("DM or active PR to github.com/jungcow/minishell\n");
}

void	print_helper(const char *str)
{
	printf("     %s     \n", str);
}

void	print_ascii_art2(void)
{
	print_helper("@@   .(((((/    (((((#############################*   &@@@@@");
	print_helper("@@   ,(((((/    (((((############################(/   ,@@@@@");
	print_helper("@&   *(((((/    ((((((###########################(/   ,@@@@@");
	print_helper("@&   ,((((((    (((((((#########################((/   &@@@@@");
	print_helper("@@    ((((((    ((((((((((####################((((.   @@@@@@");
	print_helper("@@/   ((((((    ((((((((((((((((((((((((((((((((((   /@@@@@@");
	print_helper("@@@   ,(((((,   (((((((((((((((((((((((((((((((((*   @@@@@@@");
	print_helper("@@@@            /((((((((((((/..,/(((((((((((((((    @@@@@@@");
	print_helper("@@@@@@&         .(((((((((((,             *(((((,   /@@@@@@@");
	print_helper("@@@@@@@@@@@@@.   (((((((((((    @@@&   *((((((((    @@@@@@@@");
	print_helper("@@@@@@@@@@@@@.   (((((((((((    @@@(   (((((((((   .@@@@@@@@");
	print_helper("@@@@@@@@@@@@@&   *((((((((((    @@@@   ,(((((((/   @@@@@@@@@");
	print_helper("@@@@@@@@@@@@@@   ,((((((((/    *@@@@@             @@@@@@@@@@");
	print_helper("@@@@@@@@@@@@@@&               &@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
	printf("\n\n");
	print_description();
}

void	print_ascii_art(void)
{
	printf("\n");
	print_helper("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
	print_helper("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
	print_helper("@@@@@@@@@@@@@@@@@@@@@@(                /@@@@@@@@@@@@@@@@@@@@");
	print_helper("@@@@@@@@@@@@@@@@@@@      ....               .@@@@@@@@@@@@@@@");
	print_helper("@@@@@@@@@@@@@@@@@    .##################(      ,@@@@@@@@@@@@");
	print_helper("@@@@@@@@@@@@@@@@   .########################     .@@@@@@@@@@");
	print_helper("@@@@@@@@@@@@@@@   ,(########(*.                   *@@@@@@@@@");
	print_helper("@@@@@@@@@@@@@@    (#######          .*#####(.        @@@@@@@");
	print_helper("@@@@@@@@@@@@@&   /(######    ,********@@@@@@@@@@***    @@@@@");
	print_helper("@@@@@@@@@@@@@.   ((#####(   ,**/*******@@@@@@@@@@***#   @@@@");
	print_helper("@@@@#           (((#####(   .***********************&,   @@@");
	print_helper("@@@    .####,   (((######    ********/////***********    @@@");
	print_helper("@@&   ,#####    (((######(    .********************     @@@@");
	print_helper("@@&   ((((((    (((########       ,,*********.        /@@@@@");
	print_helper("@@(   (((((/    ((((#########.                   *    @@@@@@");
	print_helper("@@.   (((((/    ((((#############&#(///(##########,   @@@@@@");
	print_ascii_art2();
}

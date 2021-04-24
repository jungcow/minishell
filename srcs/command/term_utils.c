/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jungwkim <jungwkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 19:30:16 by jungwkim          #+#    #+#             */
/*   Updated: 2021/04/23 19:31:41 by jungwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termcap.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "command/command.h"

static int  ft_nbrlen(int num)
{
    int     i;

    i = 1;
    while (num >= 10)
    {
        num /= 10;
        i++;
    }
    return (i);
}

int         get_cursor_pos(t_term *term)
{
    int     a;
    int     i;
    int     ret;
    int     temp;
    char    buf[16];

    a = 0;
    i = 0;
    temp = 0;
    write(STDIN_FILENO, "\033[6n", 4);
    ret = read(0, buf, 16);
    buf[ret] = '\0';
    while (buf[++i])
        if (buf[i] >= '0' && buf[i] <= '9')
        {
            if (a++ == 0)
                term->pos.cur_row = ft_atoi(&buf[i]) - 1;
            else
            {
                temp = ft_atoi(&buf[i]);
                term->pos.cur_col = temp - 1;
            }
            i += ft_nbrlen(temp) - 1;
        }
    return (1);
}

void        init_term_size(t_command *command, t_term *term)
{
    struct winsize  win;

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);
    term->pos.col = win.ws_col;
    term->pos.row = (command->line.length
            + ft_strlen(term->name))
            / term->pos.col;
    get_cursor_pos(term);
}

#include <termios.h>
#include <curses.h>
#include <term.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int		wrapper(int arr)
{
	write(1, &arr, 1);
	return (0);
}	

int		main()
{
	unsigned char	c;
	unsigned int	temp;
	struct	termios	term;
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ICANON;
	term.c_lflag &= ~ECHO;
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);

	while (read(0, &c, 1) > 0)
	{
		if (c == 27)
		{
			read(0, &c, 1);
			if (c == 91)
				read(0, &c, 1);
			if (c == 'C' || c == 'D')
			{
				temp = 0;
				temp = 27 + 91 * 256 + c * 256 * 256;
				write(1, &temp, 3);
			}
		}
		else
		{
			tputs("hello", 1, wrapper);
		}
	}
	return (0);
}

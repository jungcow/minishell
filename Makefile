NAME = minishell
CC = gcc
CURSES = -lncurses
INC = -I ./includes/
CFLAGS = -Wall -Werror -Wextra $(CURSES)

COMMAND_SRCS = $(addprefix ./srcs/command/, \
				command.c \
				)

SRCS = ./srcs/minishell.c \
	   $(COMMAND_SRCS)

OBJS = $(SRCS:.c=.o)

%.o : %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(INC) $(OBJS) -o $(NAME)

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all

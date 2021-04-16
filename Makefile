NAME = minishell
CC = gcc
CURSES = -lncurses
INC = -I ./includes -I ./libft
CFLAGS = -Wall -Werror -Wextra
LIB = -L./libft -lft $(CURSES)

COMMAND_SRCS = $(addprefix ./srcs/command/, \
				command.c \
				cursor.c \
				general.c \
				end.c \
				history.c \
				command_utils.c \
				)

SRCS = ./srcs/minishell.c \
		$(COMMAND_SRCS)

OBJS = $(SRCS:.c=.o)

%.o : %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

all : $(NAME)

$(NAME) : $(OBJS)
	make build_libft
	$(CC) $(OBJS) $(LIB) $(CFLAGS) -o $(NAME)

build_libft :
	make -C ./libft

clean :
	make -C ./libft clean
	rm -rf $(OBJS)

fclean : clean
	make -C ./libft fclean
	rm -rf $(NAME)

re : fclean all

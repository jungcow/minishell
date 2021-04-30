NAME = minishell
CC = gcc
CURSES = -lncurses
INC = -I ./includes -I ./libft
CFLAGS = -Wall -Werror -Wextra
LIB = -L./libft -lft $(CURSES)

##########################################################
# Builtin Part                                           #
##########################################################
ECHO = ./srcs/builtin/echo
ECHO_SRCS = $(addprefix ./srcs/builtin/srcs/echo/, \
				echo.c \
			)
ECHO_OBJS = $(ECHO_SRCS:.c=.o)


##########################################################
# Command Part                                           #
##########################################################
COMMAND_SRCS = $(addprefix ./srcs/command/, \
				command.c \
				command_utils.c \
				cursor.c \
				cursor_utils.c \
				general.c \
				end.c \
				history.c \
				term_utils.c \
				validate.c \
				validate_util.c \
				)


##########################################################
# Parse Part                                             #
##########################################################

PARSE_SRCS = $(addprefix ./srcs/parse/, \
				instruction.c \
				pipeline.c \
				operation.c \
				parse_util.c \
				split.c \
				)
##########################################################
# Execute Part                                           #
##########################################################
EXECUTE_SRCS = $(addprefix ./srcs/execute/, \
				execute.c \
				execute_utils.c \
				process.c \
				child_process.c \
				)

##########################################################
# General Rule                                           #
##########################################################

SRCS = ./srcs/minishell.c \
	   ./srcs/error.c \
		$(COMMAND_SRCS) \
		$(PARSE_SRCS) \
		$(EXECUTE_SRCS) \

OBJS = $(SRCS:.c=.o)

%.o : %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

all : $(NAME)

$(NAME) : $(OBJS) $(ECHO)
	make build_libft
	$(CC) $(OBJS) $(LIB) $(CFLAGS) -o $(NAME)


$(ECHO) : $(ECHO_OBJS)
	make build_libft
	$(CC) $(ECHO_OBJS) $(LIB) $(CFLAGS) -o $(ECHO)

build_libft : 
	make -C ./libft

clean :
	make -C ./libft clean
	rm -rf $(ECHO_OBJS)
	rm -rf $(OBJS)

fclean : clean
	make -C ./libft fclean
	rm -rf $(ECHO)
	rm -rf $(NAME)

re : fclean all

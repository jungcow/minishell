NAME = minishell
CC = gcc
CURSES = -lncurses
INC = -I ./includes -I ./libft
CFLAGS = -Wall -Werror -Wextra
LIB = -L./libft -lft $(CURSES)

##########################################################
# Builtin Part                                           #
##########################################################
BUILTIN_SRCS = $(addprefix ./srcs/builtin/, \
				echo.c \
				pwd.c \
				exit.c \
				)

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
				validate_redirect.c \
				)

##########################################################
# Parse Part                                             #
##########################################################
PARSE_SRCS = $(addprefix ./srcs/parse/, \
				instruction.c \
				pipeline.c \
				operation.c \
				operation_util.c \
				parse_util.c \
				split.c \
				redirection.c \
				)

##########################################################
# Execute Part                                           #
##########################################################
EXECUTE_SRCS = $(addprefix ./srcs/execute/, \
				execute.c \
				process.c \
				child_process.c \
				process_utils.c \
				environ/environ.c \
				environ/envlist.c \
				environ/envlist_utils.c \
				environ/envset.c \
				environ/envset_utils.c \
				)

##########################################################
# General Rule                                           #
##########################################################

SRCS = ./srcs/main.c \
	   ./srcs/minishell.c \
	   ./srcs/error.c \
	   ./srcs/signal.c \
		$(COMMAND_SRCS) \
		$(PARSE_SRCS) \
		$(EXECUTE_SRCS) \
		$(BUILTIN_SRCS) 

OBJS = $(SRCS:.c=.o)

%.o : %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

all : $(NAME)

$(NAME) : $(OBJS)
	@ touch .minish_history > /dev/null 2>&1
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

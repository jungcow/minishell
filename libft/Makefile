NAME = libft.a
CC = gcc
CFLAGS = -Wall -Werror -Wextra

SRCS = string.c \
	   ft_strncpy.c \
	   ft_strlen.c \
	   ft_strslen.c \
	   ft_split.c \
	   ft_strdup.c \
	   ft_atoi.c \
	   ft_itoa.c \
	   ft_isspace.c \
	   ft_isdigit.c \
	   ft_isalpha.c \
	   ft_isalnum.c \
	   ft_strchr.c \
	   ft_strcmp.c \
	   ft_strjoin.c \
	   ft_atoll.c \
	   get_next_line.c \
	   get_next_line_utils.c \

OBJS = $(SRCS:.c=.o)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

all : $(NAME)

$(NAME) : $(OBJS)
	ar rcs $(NAME) $(OBJS)

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all

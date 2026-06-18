NAME = libftprintf.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = ft_printf.c  ft_putnbrbase_x_maj.c ft_putchar.c ft_putnbrbase_x.c ft_putnbr.c ft_putstr.c ft_unsigned_putnbr.c ft_modulo_p.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $@ $^

clean: 
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
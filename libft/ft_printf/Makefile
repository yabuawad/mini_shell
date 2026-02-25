CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = ft_printf.c putchrnstr.c putnbr.c putptr.c putunsigned.c puthex.c 
OFILES = $(SRC:.c=.o)
NAME = libftprintf.a 

all: $(NAME)

$(NAME): $(OFILES)
	ar rcs $(NAME) $(OFILES)

clean:
	rm -f $(OFILES)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re
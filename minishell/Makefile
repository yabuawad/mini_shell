NAME		= minishell

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -I.
LDFLAGS		= -lreadline


SRCS		= minishell.c \
			  execution/builtin_execution.c \
			  execution/builtin_export_unset.c \
			  execution/path_resolver.c \
			  execution/command_execution.c \
			  execution/builtin_exit.c \
			  execution/redirections_setup.c \
			  execution/heredoc_processes.c \
			  execution/heredoc_expand.c \
			  execution/file_redirection.c \
			  execution/envp_functions.c \
			  helpers_functions/memory_utils.c \
			  helpers_functions/status_utils.c \
			  helpers_functions/error_output2.c \
			  helpers_functions/error_output.c \
			  helpers_functions/additional_files.c \
			  execution/pipes_execution.c \
			  execution/builtin_helpers.c \
			  parsing/sep.c \
			  parsing/syntax_err.c \
			  parsing/tokenise.c \
			  parsing/handle_stuff.c \
			  parsing/linkedlist.c \
			  parsing/handleparse.c \
			  parsing/parse.c \
			  parsing/expansion_helpers.c \
			  parsing/expand.c \
			  parsing/parse_process.c \
			  signals/signals.c \
			  ../libft/ft_atoi.c \
			  ../libft/ft_bzero.c \
			  ../libft/ft_calloc.c \
			  ../libft/ft_isalpha.c \
			  ../libft/ft_isalnum.c \
			  ../libft/ft_isascii.c \
			  ../libft/ft_isdigit.c \
			  ../libft/ft_isprint.c \
			  ../libft/ft_itoa.c \
			  ../libft/ft_memchr.c \
			  ../libft/ft_memcmp.c \
			  ../libft/ft_memcpy.c \
			  ../libft/ft_memmove.c \
			  ../libft/ft_memset.c \
			  ../libft/ft_putchar_fd.c \
			  ../libft/ft_putendl_fd.c \
			  ../libft/ft_putnbr_fd.c \
			  ../libft/ft_putstr_fd.c \
			  ../libft/ft_split.c \
			  ../libft/ft_strchr.c \
			  ../libft/ft_strdup.c \
			  ../libft/ft_striteri.c \
			  ../libft/ft_strjoin.c \
			  ../libft/ft_strlcat.c \
			  ../libft/ft_strlcpy.c \
			  ../libft/ft_strlen.c \
			  ../libft/ft_strmapi.c \
			  ../libft/ft_strncmp.c \
			  ../libft/ft_strnstr.c \
			  ../libft/ft_strrchr.c \
			  ../libft/ft_strtrim.c \
			  ../libft/ft_substr.c \
			  ../libft/ft_tolower.c \
			  ../libft/ft_toupper.c \
			  ../libft/ft_printf/ft_printf.c \
			  ../libft/ft_printf/putchrnstr.c \
			  ../libft/ft_printf/puthex.c \
			  ../libft/ft_printf/putnbr.c \
			  ../libft/ft_printf/putptr.c \
			  ../libft/ft_printf/putunsigned.c

OBJS		= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

NAME=	minishell
SRCS=	minishell.c env.c var.c builtin.c builtin_utils.c utils.c builtin_env.c parsing_errors.c \
		data.c pipes.c redirections.c user_input.c tokens.c tokens_utils.c quotes.c \
		tokens_utils2.c instructions.c instructions_utils.c test.c pipes_utils.c \
		user_input_utils.c cmds.c cmds_utils.c utils2.c
OBJS=	$(addprefix srcs/, $(SRCS:.c=.o))
CC=		gcc
CFLAGS=
LIBFT_DIR= libft
HEADER=	-I includes -I $(LIBFT_DIR)
LDFLAGS=	-L $(LIBFT_DIR)
LIBS=	-lft

.c.o:
	$(CC) $(CFLAGS) $(HEADER) -c $< -o $(<:.c=.o)
$(NAME):	$(OBJS)
	make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $(NAME) $(LIBS)
all: $(NAME)
clean:
	rm -f $(OBJS)
fclean: clean
	rm -f $(NAME)
re: fclean all
.PHONY: all clean fclean re

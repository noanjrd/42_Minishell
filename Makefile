NAME = minishell
CC = cc
FLAGS =  -g3
LIBS = -lreadline
RM = rm -rf

SRCS = srcs/main.c\
	srcs/utils/init.c\
	srcs/utils/utils.c\
	srcs/utils/free.c\
	srcs/utils/ft_from_libft.c\
	srcs/builtins/builtin.c\
	srcs/builtins/env.c\
	srcs/builtins/pwd.c\
	srcs/builtins/export_display.c\
	srcs/builtins/unset.c\
	srcs/builtins/cd.c\
	srcs/builtins/echo.c\
	srcs/builtins/export.c\
	srcs/builtins/exit.c\
	srcs/exec/exec.c\
	srcs/exec/relink_commands.c\
	srcs/exec/infile.c\
	srcs/exec/outfile.c\
	srcs/exec/here_doc.c\
	srcs/exec/paths.c\
	srcs/exec/prep.c\
	srcs/parsing/lexer.c\
	srcs/parsing/tokens_list.c\
	srcs/parsing/token_word.c\

OBJS = ${SRCS:.c=.o}

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(SRCS) -o $(NAME) $(LIBS)
	make clean

%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all fclean clean re
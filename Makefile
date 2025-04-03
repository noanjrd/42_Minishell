NAME = minishell
CC = cc
FLAGS =  -g3
LIBS = -lreadline
RM = rm -rf

SRCS = srcs/main.c\
	srcs/utils/utils.c\
	srcs/utils/free.c\
	srcs/utils/ft_from_libft.c\
	srcs/builtins/env.c\
	srcs/builtins/export_display.c\
	srcs/builtins/unset.c\
	srcs/builtins/cd.c\
	srcs/builtins/echo.c\
	srcs/builtins/export.c\
	srcs/builtins/exit.c\
	srcs/exec/exec.c\
	srcs/exec/paths.c

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
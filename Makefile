NAME = minishell
CC = cc
FLAGS =  -g3
LIBS = -lreadline
RM = rm -rf

SRCS = srcs/main.c\
	srcs/utils.c\
	srcs/builtin/env.c\
	srcs/builtin/export_display.c\
	srcs/builtin/unset.c\
	srcs/builtin/cd.c\
	srcs/builtin/echo.c\
	srcs/builtin/export.c

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
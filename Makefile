NAME = minishell
CC = cc
FLAGS =  -g3
RM = rm -rf

SRCS = srcs/main.c\
	srcs/utils.c\
	srcs/builtin/env.c\
	srcs/builtin/export.c

OBJS = ${SRCS:.c=.o}

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(SRCS) -o $(NAME)
	make clean

%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all fclean clean re
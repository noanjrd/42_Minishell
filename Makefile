#ENLEVER LE RELINK

NAME = minishell
CC = cc -Wall -Wextra -Werror
FLAGS = -g3 -fsanitize=address,leak
LIBS = -lreadline
RM = rm -rf
COLOR_PINK = "\001\033[38;5;205m\002"

SRCS = srcs/main.c\
	srcs/builtins/builtin.c\
	srcs/builtins/cd.c\
	srcs/builtins/cd2.c\
	srcs/builtins/echo.c\
	srcs/builtins/env.c\
	srcs/builtins/exit.c\
	srcs/builtins/exit2.c\
	srcs/builtins/export.c\
	srcs/builtins/export2.c\
	srcs/builtins/export3.c\
	srcs/builtins/pwd.c\
	srcs/builtins/unset.c\
	srcs/exec/exec.c\
	srcs/exec/exec2.c\
	srcs/exec/exec3.c\
	srcs/exec/here_doc.c\
	srcs/exec/infile.c\
	srcs/exec/infile2.c\
	srcs/exec/outfile.c\
	srcs/exec/paths.c\
	srcs/exec/paths2.c\
	srcs/exec/prep.c\
	srcs/exec/relink_commands.c\
	srcs/exec/relink_commands2.c\
	srcs/exec/relink_commands3.c\
	srcs/exec/relink_commands4.c\
	srcs/exec/relink_commands5.c\
	srcs/parsing/check_syntax.c\
	srcs/parsing/expander.c\
	srcs/parsing/expander2.c\
	srcs/parsing/expander3.c\
	srcs/parsing/lexer.c\
	srcs/parsing/merge_tokens.c\
	srcs/parsing/remove_dollar.c\
	srcs/parsing/token_word.c\
	srcs/parsing/token_word2.c\
	srcs/parsing/tokens_list.c\
	srcs/utils/create_commands.c\
	srcs/utils/create_commands2.c\
	srcs/utils/create_commands3.c\
	srcs/utils/free.c\
	srcs/utils/ft_atoll.c\
	srcs/utils/ft_from_libft.c\
	srcs/utils/ft_from_libft2.c\
	srcs/utils/ft_from_libft3.c\
	srcs/utils/init.c\
	srcs/utils/utils.c\
	srcs/utils/utils2.c\
	srcs/sig.c\

OBJS = ${SRCS:.c=.o}

BANNER_LINE_0 := ' 🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸 '
BANNER_LINE_0_5 := '🌸                                                                                    🌸'  
BANNER_LINE_1 := '🌸 ,---.    ,---..-./`) ,---.   .--..-./`) .-------. .-./`) ,---.   .--..--.   .--.   🌸'
BANNER_LINE_2 := '🌸 |    \  /    |\ .-.`)|    \  |  |\ .-.`)\  _(`)_ \\ .-.`)|    \  |  ||  | _/  /    🌸'
BANNER_LINE_3 := '🌸 |  ,  \/  ,  |/ `-´ \|  ,  \ |  |/ `-´ \| (_ o._)|/ `-´ \|  ,  \ |  || (`´\'' ) /    🌸'
BANNER_LINE_4 := '🌸 |  |\_   /|  | `-´`"`|  |\_ \|  | `-´`"`|  (_,_) / `-´`"`|  |\_ \|  ||(_ ()_)      🌸'
BANNER_LINE_5 := '🌸 |  _( )_/ |  | .---. |  _( )_\  | .---. |   '\''-.-'\''  .---. |  _( )_\  || (_,_)   __  🌸'
BANNER_LINE_6 := '🌸 | (_ o _) |  | |   | | (_ o _)  | |   | |   |      |   | | (_ o _)  ||  |\ \  |  | 🌸'
BANNER_LINE_7 := '🌸 |  (_,_)  |  | |   | |  (_,_)\  | |   | |   |      |   | |  (_,_)\  ||  | \ `'\''   / 🌸'
BANNER_LINE_8 := '🌸 |  |      |  | |   | |  |    |  | |   | /   )      |   | |  |    |  ||  |  \    /  🌸'
BANNER_LINE_9 := '🌸 '\''--'\''      '\''--'\'' '\''---'\'' '\''--'\''    '\''--'\'' '\''---'\'' `---'\''      '\''---'\'' '\''--'\''    '\''--'\''`--'\''   `'\''-'\''   🌸'
BANNER_LINE_10 := '🌸                                                                                    🌸'  
BANNER_LINE_11 := ' 🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸🌸 '

all: banner $(NAME)

banner:
	@printf '\033[38;5;218m%s\033[0m\n' $(BANNER_LINE_0)
	@printf '\033[38;5;218m%s\033[0m\n' $(BANNER_LINE_0_5)
	@printf '\033[38;5;218m%s\033[0m\n' $(BANNER_LINE_1)
	@printf '\033[38;5;218m%s\033[0m\n' $(BANNER_LINE_2)
	@printf '\033[38;5;218m%s\033[0m\n' $(BANNER_LINE_3)
	@printf '\033[38;5;218m%s\033[0m\n' $(BANNER_LINE_4)
	@printf '\033[38;5;218m%s\033[0m\n' $(BANNER_LINE_5)
	@printf '\033[38;5;218m%s\033[0m\n' $(BANNER_LINE_6)
	@printf '\033[38;5;218m%s\033[0m\n' $(BANNER_LINE_7)
	@printf '\033[38;5;218m%s\033[0m\n' $(BANNER_LINE_8)
	@printf '\033[38;5;218m%s\033[0m\n' $(BANNER_LINE_9)
	@printf '\033[38;5;218m%s\033[0m\n' $(BANNER_LINE_10)
	@printf '\033[38;5;218m%s\033[0m\n' $(BANNER_LINE_11)
	@echo ""

$(NAME): $(OBJS)
	@echo "Compiling $(NAME)..."
	@$(CC) $(FLAGS) $(OBJS) -o $(NAME) $(LIBS)
	@echo "🌸 $(NAME) compiled successfully.🌸"
	@make clean 

%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	@echo "Cleaning object files... 🧹"
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)
	@echo '✨ Cleaned successfully ✨'

re: fclean all

.PHONY: all fclean clean re banner

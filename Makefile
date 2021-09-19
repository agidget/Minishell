NAME = minishell

HEADER = minishell.h

SRC =	main.c\
        ./parsing/parsing.c\
        ./parsing/dollar.c\
        ./parsing/if_quote.c\
        ./parsing/utils_for_pars.c\
        ./parsing/utils_for_pars2.c\
        ./parsing/main_parser.c\
        ./parsing/redirection.c\
        ./parsing/create_struct.c\
        ./parsing/signals.c\
		./parsing/for_execve.c\
		./parsing/for_redirection.c\
		./parsing/change_shell_level.c\
		./parsing/utils_for_quotes.c\
		./parsing/utils_create_struct.c\
		./parsing/utils_create_struct2.c\
		./parsing/for_dollar.c\
        ./execution/pipes.c\
		./execution/pipes2.c\
		./execution/pipes3.c\
		./execution/pipes4.c\
        ./execution/envp_value.c\
		./utils/errors_funct.c\
		./utils/errors_funct2.c\
        ./utils/functions.c\
		./utils/functions2.c\
		./utils/functions3.c\
        ./utils/print_functions.c\
        ./builtins/builtin_functions.c\
        ./builtins/for_cd.c\
		./builtins/for_cd_utils1.c\
        ./builtins/for_path.c\
        ./builtins/for_echo.c\
		./builtins/for_env.c\
		./builtins/for_env_lists.c\
		./builtins/for_exit.c\
		./builtins/for_export.c\
		./builtins/for_pwd.c\
		./builtins/for_unset.c\
		./builtins/for_cd_utils2.c
	
LIBFT = ./Libft/libft.a

OBJ = $(patsubst %.c, %.o, $(SRC))

CC = gcc -Wall -Wextra -Werror

INCLUDES = -I./ -I./Libft -I ~/.brew/opt/readline/include

READLINE = -lreadline -L ~/.brew/opt/readline/lib

FLAGS = -lreadline

$(NAME):	$(OBJ)
	make -C ./Libft/
	$(CC) $(INCLUDES) $(OBJ) $(LIBFT) $(READLINE) -o $@

%.o : %.c $(HEADER)
	$(CC) -c -g $< -o $@ $(INCLUDES)

clean:
	rm -f $(OBJ)
	make -C ./Libft/ clean

fclean:
	rm -f $(OBJ) $(NAME)
	make -C ./Libft/ fclean

all : $(NAME)

re: fclean all

.PHONY: clean fclean re all

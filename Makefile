# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/03 01:59:13 by hatesfam          #+#    #+#              #
#    Updated: 2023/11/07 16:54:59 by hatesfam         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

# Colors:
GREEN		=	\e[92;5;118m
GRAY		=	\e[33;2;37m
RED         =   \e[91m
RESET		=	\e[0m
CURSIVE		=	\e[33;3m

CC = cc -g3
sanitizer = -fsanitize=address -fno-omit-frame-pointer
INC = ./includes
RDLINE_L = -L/Users/$(USER)/.brew/opt/readline/lib -lreadline
LIBFT = ./includes/libft/libft.a
CFALGS = -Wall -Werror -Wextra -I$(INC)
RM = rm -rf

# Source file directories:
LEXER_DIR = ./src/lexer
PARSER_DIR = ./src/parser
EXPANDER_DIR = ./src/expander
HELPER_DIR = ./src/helpers
EXTRACT_DIR = ./src/cmd_extractor
EXEC_DIR = ./src/executer
BUILTINS_DIR = ./src/builtins

# Source files:
SRC_FILES = src/minishell.c  src/init_minishell.c\
			$(HELPER_DIR)/err_printer.c $(HELPER_DIR)/is_funcs.c $(HELPER_DIR)/env_dl.c $(HELPER_DIR)/ft_error.c $(HELPER_DIR)/one_space_setter.c $(HELPER_DIR)/cleaner_utils.c $(HELPER_DIR)/cleaner_arr.c \
			$(HELPER_DIR)/splitter.c $(HELPER_DIR)/printer.c $(HELPER_DIR)/cleaner.c \
			$(LEXER_DIR)/tokenize_input.c $(LEXER_DIR)/token_lst.c \
			$(EXPANDER_DIR)/var_expander.c $(EXPANDER_DIR)/var_expander_utils.c $(EXPANDER_DIR)/expand_utils.c $(EXPANDER_DIR)/remove_qoutes.c\
			$(EXTRACT_DIR)/extract_cmd.c $(EXTRACT_DIR)/extract_cmd_utils.c $(EXTRACT_DIR)/cmd_lst.c $(EXTRACT_DIR)/extract_operator.c $(EXTRACT_DIR)/init_iofds.c $(EXTRACT_DIR)/here_doc.c $(EXTRACT_DIR)/here_doc_utils.c\
			$(EXEC_DIR)/pre_exec.c $(EXEC_DIR)/start_execution.c $(EXEC_DIR)/valid_cmd.c $(EXEC_DIR)/pipes.c $(EXEC_DIR)/redirect_iofds.c $(EXEC_DIR)/builtins.c $(EXEC_DIR)/fd_close.c  \
			$(BUILTINS_DIR)/unset.c $(BUILTINS_DIR)/exit.c $(BUILTINS_DIR)/echo.c  $(BUILTINS_DIR)/export.c $(BUILTINS_DIR)/cd.c\
			#  $(BUILTINS_DIR)/env.c $(BUILTINS_DIR)/pwd.c  \

# Object files:
OBJ_FILES = $(SRC_FILES:.c=.o)

# Rule for generating object files:
%.o: %.c
	@printf "$(CURSIVE)$(GRAY)	~ Making object file $(notdir $@) from source file $(notdir $<) ... $(RESET)\n"
	@$(CC) -c $(CFALGS) $< -o $@

all: $(NAME)

# Rule for generating the executable:
$(NAME): $(OBJ_FILES)
	@$(MAKE) -C ./includes/libft
	@printf "$(CURSIVE)$(GRAY) 	- Compiling $(NAME)... $(RESET)\n"
	@$(CC) $(CFALGS) $^ $(LIBFT) $(RDLINE_L) -o $@ -I$(INC)
	@printf "$(GREEN)    - Minishell Executable ready.\n$(RESET)"
	clear
# Rule for cleaning object files:	
clean:
	@$(MAKE) -C ./includes/libft clean
	@$(RM) $(OBJ_FILES)
	@printf "$(CURSIVE)$(GRAY)	- Removing object files ... $(RESET)\n"
	@printf "$(RED)    - Object files removed.$(RESET)\n"
	clear

# Rule for cleaning object files, archives and executable:
fclean: clean
	@$(MAKE) -C ./includes/libft fclean
	@$(RM) $(NAME)
	@printf "$(CURSIVE)$(GRAY)	- Removing $(NAME)... $(RESET)\n"
	@printf "$(RED)    - Executable & Archives removed.$(RESET)\n"
	clear

# Rule for re-making the executable:	
re: fclean all
	@printf "$(CURSIVE)$(GRAY)	- Remaking $(NAME)... $(RESET)\n"
	clear

# Rule for easy re-run
s: all
	clear
	./minishell

# Rule to run and check for memory leaks (inside docker only)
leaks:
	@make all
	valgrind --suppressions=readleak.txt --leak-check=full --trace-children=yes \
	--show-leak-kinds=all --track-origins=yes --track-fds=yes ./minishell
# Phony targets:
.PHONY: all clean fclean re
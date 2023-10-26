# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/03 01:59:13 by hatesfam          #+#    #+#              #
#    Updated: 2023/10/26 20:56:24 by hatesfam         ###   ########.fr        #
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

# Source files:
SRC_FILES = src/minishell.c \
			$(LEXER_DIR)/tokenize_input.c $(LEXER_DIR)/cmd_elem_lst.c \
			$(EXPANDER_DIR)/var_expander.c $(EXPANDER_DIR)/expand_utils.c $(EXPANDER_DIR)/remove_qoutes.c\
			$(EXTRACT_DIR)/extract_cmd.c $(EXTRACT_DIR)/extract_cmd_utils.c $(EXTRACT_DIR)/dl_lst.c $(EXTRACT_DIR)/extract_operator.c \
			$(EXTRACT_DIR)/init_iofds.c $(EXTRACT_DIR)/here_doc.c \
			$(HELPER_DIR)/is_funcs.c $(HELPER_DIR)/ft_error.c $(HELPER_DIR)/one_space_setter.c $(HELPER_DIR)/cleaner_utils.c $(HELPER_DIR)/cleaner_arr.c\
			$(HELPER_DIR)/splitter.c $(HELPER_DIR)/printer.c $(HELPER_DIR)/cleaner.c

# Object files:
OBJ_FILES = $(SRC_FILES:.c=.o)

# Rule for generating object files:
%.o: %.c
	@printf "$(CURSIVE)$(GRAY)	~ Making object file $(notdir $@) from source file $(notdir $<) ... $(RESET)\n"
	@$(CC) -c $(CFALGS) $< -o $@

all: $(NAME)

leaks: 
	valgrind --suppressions=readleak.txt --leak-check=full --trace-children=yes \
	--show-leak-kinds=all --track-origins=yes --track-fds=yes ./minishell

# Rule for generating the executable:
$(NAME): $(OBJ_FILES)
	@$(MAKE) -C ./includes/libft
	@printf "$(CURSIVE)$(GRAY) 	- Compiling $(NAME)... $(RESET)\n"
	@$(CC) $(CFALGS) $^ $(LIBFT) $(RDLINE_L) -o $@ -I$(INC)
	@printf "$(GREEN)    - Minishell Executable ready.\n$(RESET)"
	@$(RM) $(OBJ_FILES)
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
	@$(RM) $(OBJ_FILES)
	clear

#<------- delete later------>
s: all
	clear
	./minishell
f: re
	clear
	./minishell

p: fclean
	git add .
	git commit -m "Updated on $(shell date +'%Y-%m-%d %H:%M:%S') by $(shell whoami)"
	git push -u origin master

#Debug 
ifeq ($(DEBUG), 1)
   OPTS = -g
endif

lldb:
	@make fclean && make DEBUG=1 && lldb minishell
#<------- delete later------>

# Phony targets:
.PHONY: all clean fclean re
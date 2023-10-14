# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/03 01:59:13 by hatesfam          #+#    #+#              #
#    Updated: 2023/10/14 18:30:48 by hatesfam         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# $(VERBOSE).SILENT:

NAME = minishell

CC = cc
sanitizer = -fsanitize=address -g3 -fno-omit-frame-pointer
INC = ./includes
RDLINE_L = -lreadline -L/usr/local/opt/readline/lib
LIBFT = ./includes/libft/libft.a
CFALGS = -Wall -Werror -Wextra -I$(INC) $(sanitizer)
RM = rm -rf

PARSER_DIR = ./src/parser
HELPER_DIR = ./src/helpers

SRC_FILES = src/minishell.c $(PARSER_DIR)/check_input_cmd.c $(PARSER_DIR)/dl_lst.c \
			$(PARSER_DIR)/tokenize_cmd.c $(PARSER_DIR)/cmd_elem_lst.c $(HELPER_DIR)/is_funcs.c $(HELPER_DIR)/ft_error.c\
			$(HELPER_DIR)/one_space_setter.c $(HELPER_DIR)/ft_clean_arr.c

OBJ_FILES = $(SRC_FILES:.c=.o)

#Colors:
GREEN		=	\e[92;5;118m
GRAY		=	\e[33;2;37m
RED         =   \e[91m
RESET		=	\e[0m
CURSIVE		=	\e[33;3m

%.o: %.c
	@printf "$(CURSIVE)$(GRAY) 	- Making object file $(notdir $@) from source file $(notdir $<) ... $(RESET)\n"
	@$(CC) -c $(CFALGS) $< -o $@

all: $(NAME)

$(NAME): $(OBJ_FILES)
	@$(MAKE) -C ./includes/libft
	@printf "$(CURSIVE)$(GRAY) 	- Compiling $(NAME)... $(RESET)\n"
	@$(CC) $(CFALGS) $^ $(LIBFT) $(RDLINE_L) -o $@ -I$(INC)
	@printf "$(GREEN)    - Minishell Executable ready.\n$(RESET)"
	
clean:
	@$(MAKE) -C ./includes/libft clean
	@$(RM) $(OBJ_FILES)
	@printf "$(CURSIVE)$(GRAY)	- Removing object files ... $(RESET)\n"
	@printf "$(RED)    - Object files removed.$(RESET)\n"
	
fclean: clean
	@$(MAKE) -C ./includes/libft fclean
	@$(RM) $(NAME)
	@printf "$(CURSIVE)$(GRAY)	- Removing $(NAME)... $(RESET)\n"
	@printf "$(RED)    - Executable & Archives removed.$(RESET)\n"
	
re: fclean all
	clear

go: re
	./minishell
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

.PHONY: all clean fclean re
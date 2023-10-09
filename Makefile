# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/03 01:59:13 by hatesfam          #+#    #+#              #
#    Updated: 2023/10/09 07:11:11 by hatesfam         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# $(VERBOSE).SILENT:

NAME = minishell

CC = cc
CFALGS = -Wall -Werror -Wextra -g3
RM = rm -rf

PARSE_DIR = ./src/parser

SRC_FILES = src/minishell.c $(PARSE_DIR)/check_input_cmd.c $(PARSE_DIR)/dl_lst.c \
			$(PARSE_DIR)/ft_error.c $(PARSE_DIR)/ft_tokenize.c $(PARSE_DIR)/ft_whitespaces.c

OBJ_FILES = $(SRC_FILES:.c=.o)
INC = ../includes
RDLINE_L = -lreadline
LIBFT = ./includes/libft/libft.a

%.o: %.c
	@$(CC) -c $(CFALGS) $< -o $@

all: $(NAME)

$(NAME): $(OBJ_FILES)
	@$(MAKE) -C ./includes/libft
	$(CC) $(CFALGS) $^ $(LIBFT) $(RDLINE_L) -o $@ -I$(INC)
	
clean:
	@$(MAKE) -C ./includes/libft fclean
	$(RM) $(OBJ_FILES)
	
fclean: clean
	$(RM) $(NAME)
	
re: fclean all

push: fclean
	git add .
	git commit -m "Updated on $(shell date +'%Y-%m-%d %H:%M:%S') by $(shell whoami)"
	git push -u origin master

.PHONY: all clean fclean re push
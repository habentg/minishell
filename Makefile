# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/03 01:59:13 by hatesfam          #+#    #+#              #
#    Updated: 2023/10/03 05:40:34 by hatesfam         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# $(VERBOSE).SILENT:

NAME = minishell

CC = cc
CFALGS = -Wall -Werror -Wextra -g3
RM = rm -rf

SRC_FILES = src/minishell.c
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

.PHONY: all clean fclean re
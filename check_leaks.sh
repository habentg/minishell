# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    check_leaks.sh                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/01 19:15:04 by hatesfam          #+#    #+#              #
#    Updated: 2023/12/01 22:21:38 by hatesfam         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Rule to run and check for memory leaks (inside docker only)
leaks:
	valgrind --suppressions=readleak.txt --leak-check=full --trace-children=yes \
	--show-leak-kinds=all --track-origins=yes --track-fds=yes ./minishell
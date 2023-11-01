# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    process_check.sh                                   :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/01 01:42:06 by hatesfam          #+#    #+#              #
#    Updated: 2023/11/01 01:42:15 by hatesfam         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

if [ $$ -eq $PPID ]; then
    echo "I am in the parent process"
else
    echo "I am in the child process"
fi
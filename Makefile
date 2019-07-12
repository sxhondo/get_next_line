# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/28 18:25:53 by sxhondo           #+#    #+#              #
#    Updated: 2019/05/29 14:26:46 by sxhondo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	gnl	

SRC 	= 	get_next_line.c

INC		=	get_next_line.h

CC 		=	-gcc

FLAGS	=	-Wall -Wextra -Werror


all: clean $(NAME)


$(NAME):
		$(CC) $(FLAGS) $(SRC) main.c -L./libft/ -lft -o $(NAME)

test:
		$(CC) $(SRC) -L./libft/ -lft -o $(NAME)

clean:
		@/bin/rm -f $(NAME)

re:     clean all

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: araji-af <araji-af@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/22 19:49:54 by araji-af          #+#    #+#              #
#    Updated: 2023/05/25 20:04:13 by araji-af         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = initialise.c parsing.c processing.c utils.c main.c

NAME = philo

OBJ = $(SRCS:.c=.o)

FLAGS = -Wall -Wextra -Werror

%.o : %.c philo.h
	cc $(FLAGS) -c $< -o $@ 

all : $(NAME)

$(NAME) : $(OBJ)
	cc $(FLAGS) $(OBJ) -o $(NAME)

clean :
	rm -rf $(OBJ)
	
fclean : clean
	rm -rf $(NAME)

re : fclean all
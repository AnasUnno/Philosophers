# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: araji-af <araji-af@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/22 19:49:54 by araji-af          #+#    #+#              #
#    Updated: 2023/06/01 16:52:45 by araji-af         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = initialise.c parsing.c processing.c utils.c main.c ft_strcmp.c

NAME = philo_bonus

OBJ = $(SRCS:.c=.o)

FLAGS = -Wall -Wextra -Werror

%.o : %.c philo_bonus.h
	cc $(FLAGS) -c $< -o $@ 

all : $(NAME)

$(NAME) : $(OBJ)
	cc $(FLAGS) $(OBJ) -o $(NAME)

clean :
	rm -rf $(OBJ)
	
fclean : clean
	rm -rf $(NAME)

re : fclean all
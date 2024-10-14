# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: razaccar <razaccar@student.42lausanne.c    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/02 18:44:43 by razaccar          #+#    #+#              #
#    Updated: 2024/10/14 11:24:06 by razaccar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= philo

SRC_DIR 	:= src
SRC 		:= $(wildcard $(SRC_DIR)/*.c)
OBJ			:= $(SRC:.c=.o)

CC 			= gcc
CCFLAGS		+= -Wall -Wextra -Werror
# CCFLAGS 	:= -fsanitize=thread -g 

REMOVE		:= rm -f

green 		:= \033[0;32m

# **************************************************************************** #

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CCFLAGS) $(OBJ) -o $(NAME)
	@echo "$(green)$(NAME) program compiled."

%.o: %.c
	$(CC) $(CCFLAGS) -c $< -o $@

clean:
	$(REMOVE) $(OBJ)

fclean: clean
	$(REMOVE) $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re

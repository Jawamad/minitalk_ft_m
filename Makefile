# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: flmuller <flmuller@student.42perpignan.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/16 15:20:27 by florian           #+#    #+#              #
#    Updated: 2024/05/17 09:54:19 by flmuller         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# **************************************************************************** #
#                                   CONFIG                                     #
# **************************************************************************** #

CC = gcc
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror -g
NAME_CLIENT = client
NAME_SERVER = server

# **************************************************************************** #
#                                   FILES                                      #
# **************************************************************************** #

SRC_CLIENT	= src/client.c src/utils.c src/utils_str.c
SRC_SERVER	= src/server.c src/utils.c src/utils_str.c

# **************************************************************************** #
#                                   PATH                                       #
# **************************************************************************** #

OBJ_SERVER = $(SRC_SERVER:.c=.o)
OBJ_CLIENT = $(SRC_CLIENT:.c=.o)

# **************************************************************************** #
#                                   RULES                                      #
# **************************************************************************** #

all : $(NAME_SERVER) $(NAME_CLIENT)

$(NAME_SERVER): $(OBJ_SERVER)
	$(CC) $(CFLAGS) $(OBJ_SERVER) -o $(NAME_SERVER)
$(NAME_CLIENT): $(OBJ_CLIENT)
	$(CC) $(CFLAGS) $(OBJ_CLIENT) -o $(NAME_CLIENT)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ_SERVER) $(OBJ_CLIENT)

fclean: clean
	@$(RM) $(NAME_CLIENT) $(NAME_SERVER)

re : fclean all

.PHONY: all bonus clean fclean re

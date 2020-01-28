# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/27 13:59:45 by sxhondo           #+#    #+#              #
#    Updated: 2020/01/27 13:59:46 by sxhondo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = dasm
CC = gcc
# CFLAGS = -Wall -Wextra -Werror
CFLAGS = -g

INC_DIR = incs/
INC  = $(INC_DIR)dasm.h

LIB_DIR = libft/
LIB_FT = $(LIB_DIR)libft.a

SRCS_DIR = srcs/
SRCS_LIST =	main.c\
			dasm_parser.c init_parser.c\
			display_helper.c

OBJ_DIR = obj/
OBJ_LIST = $(SRCS_LIST:%.c=%.o)
OBJECTS = $(addprefix $(OBJ_DIR), $(OBJ_LIST))

all: $(NAME)

$(NAME): $(LIB_FT) $(OBJ_DIR) $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -L $(LIB_DIR) -lft -o $(NAME)

$(OBJ_DIR)%.o: $(SRCS_DIR)%.c $(INC)
	$(CC) -c $< -o $@ $(CFLAGS) -I $(INC_DIR) -I $(addprefix $(LIB_DIR), $(INC_DIR))

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(LIB_FT): $(LIB_DIR)
	@make -C $(LIB_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@make clean -C $(LIB_DIR)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIB_DIR)

re: fclean all

.PHONY: all clean fclean re%

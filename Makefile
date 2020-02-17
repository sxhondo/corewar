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

CC = 				gcc
#CFLAGS = -Wall -Wextra -Werror
CFLAGS = 			-g

INC_DIR = 			incs/
LIB_DIR = 			libft/
LIB_FT = 			$(LIB_DIR)libft.a
OBJ_DIR = 			obj/

DASM = 				dasm
DASM_INC = 			$(INC_DIR)dasm.h
DASM_SRCS_DIR = 	srcs_dasm/
DASM_SRCS_LIST =	dasm.c \
					write_to_file.c\
					dasm_parser.c init_dasm_parser.c\
					dasm_utilities.c
DASM_OBJ_LIST = 	$(DASM_SRCS_LIST:%.c=%.o)
DASM_OBJECTS = 		$(addprefix $(OBJ_DIR), $(DASM_OBJ_LIST))

all: $(ASM) $(DASM)

$(DASM): $(LIB_FT) $(OBJ_DIR) $(DASM_OBJECTS)
	$(CC) $(CFLAGS) $(DASM_OBJECTS) -L $(LIB_DIR) -lft -o $(DASM)

$(OBJ_DIR)%.o: $(DASM_SRCS_DIR)%.c $(DASM_INC)
	$(CC) -c $< -o $@ $(CFLAGS) -I $(INC_DIR) -I $(addprefix $(LIB_DIR), $(INC_DIR))

ASM = 				asm
ASM_INC = 			$(INC_DIR)asm.h
ASM_SRCS_DIR = 		srcs_asm/
ASM_SRCS_LIST =		asm.c asm_parser.c lexer.c syntaxer.c analyzer.c\
					asm_utilities.c init.c int_converters.c error.c\
					s_utils.c skipers.c dasm_utilities.c\

ASM_OBJ_LIST = 		$(ASM_SRCS_LIST:%.c=%.o)
ASM_OBJECTS = 		$(addprefix $(OBJ_DIR), $(ASM_OBJ_LIST))

$(ASM): $(LIB_FT) $(OBJ_DIR) $(ASM_OBJECTS)
	$(CC) $(CFLAGS) $(ASM_OBJECTS) -L $(LIB_DIR) -lft -o $(ASM)

$(OBJ_DIR)%.o: $(ASM_SRCS_DIR)%.c $(ASM_INC)
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

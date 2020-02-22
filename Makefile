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
SRC_DIR = 			srcs/

ASM = 				asm
ASM_INC = 			$(INC_DIR)
ASM_SRCS_DIR = 		$(SRC_DIR)srcs_asm/
MAIN =				$(SRC_DIR)assembler.c
ASM_SRCS_LIST =		asm.c\
					lexer.c syntaxer.c analyzer.c\
					asm_utilities.c error.c init.c int_converters.c\
					s_utils.c skipers.c write_byte_code.c write_cor_file.c

ASM_OBJ_LIST = 		$(ASM_SRCS_LIST:%.c=%.o)
ASM_OBJECTS = 		$(addprefix $(OBJ_DIR), $(ASM_OBJ_LIST))


DASM_SRC_DIR = 		$(SRC_DIR)srcs_dasm/
DASM_SRC_LIST = 	dasm_parser.c dasm_utilities.c init_dasm_parser.c\
					write_s_file.c
DASM_OBJ_LIST =		$(DASM_SRC_LIST:%.c=%.o)
DASM_OBJECTS = 		$(addprefix $(OBJ_DIR), $(DASM_OBJ_LIST))


all: $(ASM)

$(ASM): $(LIB_FT) $(OBJ_DIR) $(ASM_OBJECTS) $(DASM_OBJECTS)
	$(CC) $(CFLAGS) $(MAIN) $(DASM_OBJECTS) $(ASM_OBJECTS) -I $(INC_DIR) -I $(addprefix $(LIB_DIR), $(INC_DIR)) -L $(LIB_DIR) -lft -o $(ASM)

$(OBJ_DIR)%.o: $(ASM_SRCS_DIR)%.c
	$(CC) -c $< -o $@ $(CFLAGS) -I $(INC_DIR) -I $(addprefix $(LIB_DIR), $(INC_DIR))

$(OBJ_DIR)%.o: $(DASM_SRC_DIR)%.c
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
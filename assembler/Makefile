# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/27 13:59:45 by sxhondo           #+#    #+#              #
#    Updated: 2020/02/24 13:55:05 by bdudley          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = 				gcc
CFLAGS = 			-Wall -Wextra -Werror

INC_DIR = 			incs/
LIB_DIR = 			../libft/
LIB_FT = 			$(LIB_DIR)libft.a
OBJ_DIR = 			obj/
SRC_DIR = 			srcs/

INCS =				op.h general.h asm.h dasm.h
INC_LIST = 			$(addprefix $(INC_DIR), $(INCS))

ASM = 				asm
ASM_INC = 			$(INC_DIR)

COMMON_SRCS_LIST =	assembler.c
COMMON_OBJ_LIST =	$(COMMON_SRCS_LIST:%.c=%.o)
COMMON_OBJECTS = 	$(addprefix $(OBJ_DIR), $(COMMON_OBJ_LIST))


ASM_SRCS_DIR = 		$(SRC_DIR)srcs_asm/
ASM_SRCS_LIST =		asm.c lexer.c syntaxer.c analyzer.c\
					asm_utils.c lexer_utils.c s_utils.c\
					calculate_distance.c error.c init.c\
					int_converters.c is.c write_byte_code.c

ASM_OBJ_LIST = 		$(ASM_SRCS_LIST:%.c=%.o)
ASM_OBJECTS = 		$(addprefix $(OBJ_DIR), $(ASM_OBJ_LIST))


DASM_SRC_DIR = 		$(SRC_DIR)srcs_dasm/
DASM_SRC_LIST = 	check_exec_code.c dasm_parser.c get_arg.c\
					d_init.c dasm_utilities.c write_asm_file.c

DASM_OBJ_LIST =		$(DASM_SRC_LIST:%.c=%.o)
DASM_OBJECTS = 		$(addprefix $(OBJ_DIR), $(DASM_OBJ_LIST))


all: $(ASM)

$(ASM): $(OBJ_DIR) $(ASM_OBJECTS) $(DASM_OBJECTS) $(COMMON_OBJECTS) $(INC_LIST)
	$(CC) $(CFLAGS) $(MAIN) $(DASM_OBJECTS) $(ASM_OBJECTS) $(COMMON_OBJECTS) -L $(LIB_DIR) -lft -o $(ASM)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INC_LIST)
	$(CC) -c $(CFLAGS) $< -o $@ -I $(INC_DIR) -I $(addprefix $(LIB_DIR), $(INC_DIR))

$(OBJ_DIR)%.o: $(ASM_SRCS_DIR)%.c $(INC_LIST)
	$(CC) -c $(CFLAGS) $< -o $@ -I $(INC_DIR) -I $(addprefix $(LIB_DIR), $(INC_DIR))

$(OBJ_DIR)%.o: $(DASM_SRC_DIR)%.c $(INC_LIST)
	$(CC) -c $(CFLAGS) $< -o $@ -I $(INC_DIR) -I $(addprefix $(LIB_DIR), $(INC_DIR))

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(ASM)

re: fclean all

.PHONY: all clean fclean re%

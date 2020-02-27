# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ylila <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/11 03:21:36 by ylila             #+#    #+#              #
#    Updated: 2019/08/17 21:15:43 by mdeanne          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
LIB_NAME = ./libft/libft.a

FLAGS = -Wall -Wextra -Werror

SRC_GEN = ./srcs/
SRC_FLOAT = ./srcsFloat/
HEAD_PATH = ./includes/
LIB_PATH = ../libft/

SRC_FILES_GEN = field_len.c fill_union.c ft_itoa_base_printf.c ft_printf.c get_binary.c is_parser.c is_typeflags.c \
	make_field.c parsing_funcs.c parsing_generaly.c prepare_lennum.c set_buff.c set_flags.c str_tolower.c \
	to_buff.c which_sign.c zeroing.c

SRC_FILES_FLOAT = check_create_float_res.c e_flag_intf.c float_intf.c float_rounding.c frees_for_float.c ft_log10.c \
	ft_log2.c g_flag_intf.c get_dbl_values.c get_ldbl_values.c high_precision.c high_precision_intf.c \
	high_precision_intf_long.c high_precision_long.c my_float.c my_long_float.c print_reserve_dbl.c

SRCS_GEN = $(addprefix $(SRC_GEN),$(SRC_FILES_GEN))
SRCS_FLOAT = $(addprefix $(SRC_FLOAT),$(SRC_FILES_FLOAT))

OBJS = $(SRC_FILES_GEN:.c=.o) $(SRC_FILES_FLOAT:.c=.o)

print-%:
	@echo $*=$($*)

all: $(NAME)

$(NAME): $(LIB_NAME) $(OBJS)
	@cp ../libft/libft.a ./$(NAME)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)

$(LIB_NAME):
	@make -C $(LIB_PATH) re

$(OBJS):
	@gcc -c $(SRCS_GEN) $(FLAGS) -I$(HEAD_PATH) -I$(LIB_PATH) -O3
	@gcc -c $(SRCS_FLOAT) $(FLAGS) -I$(HEAD_PATH) -I$(LIB_PATH) -O3

clean:
	@rm -f $(OBJS)
	@make -C $(LIB_PATH) clean

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIB_PATH) fclean

re: fclean all

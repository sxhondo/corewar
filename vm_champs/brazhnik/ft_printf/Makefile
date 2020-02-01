#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vbrazhni <vbrazhni@student.unit.ua>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/27 23:28:05 by vbrazhni          #+#    #+#              #
#    Updated: 2018/10/27 23:28:06 by vbrazhni         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = libftprintf.a

CC = gcc
FLAGS = -Wall -Werror -Wextra -O3
INCLUDES = -I$(HEADERS_DIRECTORY) -I$(LIBFT_HEADERS_DIRECTORY)

# LIBFT

LIBFT = $(LIBFT_DIRECTORY)libft.a
LIBFT_DIRECTORY = ./libft/

# LIBFT_HEADERS

LIBFT_HEADERS_LIST = \
	libft.h
LIBFT_HEADERS_DIRECTORY = $(LIBFT_DIRECTORY)includes/
LIBFT_HEADERS = $(addprefix $(LIBFT_HEADERS_DIRECTORY), $(LIBFT_HEADERS_LIST))

# LIBFT_SOURCES

LIBFT_SOURCES_DIRECTORY = $(LIBFT_DIRECTORY)sources/
LIBFT_SOURCES_LIST = \
	ft_memset.c\
	ft_bzero.c\
	ft_memcpy.c\
	ft_memccpy.c\
	ft_memmove.c\
	ft_memchr.c\
	ft_memcmp.c\
	ft_strlen.c\
	ft_strdup.c\
	ft_strcpy.c\
	ft_strncpy.c\
	ft_strcat.c\
	ft_strncat.c\
	ft_strlcat.c\
	ft_strchr.c\
	ft_strrchr.c\
	ft_strstr.c\
	ft_strnstr.c\
	ft_strcmp.c\
	ft_strncmp.c\
	ft_atoi.c\
	ft_isalpha.c\
	ft_isdigit.c\
	ft_isalnum.c\
	ft_isascii.c\
	ft_isprint.c\
	ft_toupper.c\
	ft_tolower.c\
	ft_memalloc.c\
	ft_memdel.c\
	ft_strnew.c\
	ft_strdel.c\
	ft_strclr.c\
	ft_striter.c\
	ft_striteri.c\
	ft_strmap.c\
	ft_strmapi.c\
	ft_strequ.c\
	ft_strnequ.c\
	ft_strsub.c\
	ft_strjoin.c\
	ft_strtrim.c\
	ft_strsplit.c\
	ft_itoa.c\
	ft_putchar.c\
	ft_putstr.c\
	ft_putendl.c\
	ft_putnbr.c\
	ft_putchar_fd.c\
	ft_putstr_fd.c\
	ft_putendl_fd.c\
	ft_putnbr_fd.c\
	ft_lstnew.c\
	ft_lstdelone.c\
	ft_lstdel.c\
	ft_lstadd.c\
	ft_lstiter.c\
	ft_lstmap.c\
	ft_isupper.c\
	ft_islower.c\
	ft_isspace.c\
	ft_isblank.c\
	ft_strnlen.c\
	ft_strndup.c\
	ft_lstaddback.c\
	ft_strlwr.c\
	ft_strupr.c\
	ft_strrev.c\
	ft_strchrs.c\
	ft_strsubchr.c\
	get_next_line.c\
	ft_percent.c\
	ft_arrindex.c\
	ft_isdigit_base.c\
	ft_isprefix.c\
	ft_isnum.c\
	ft_signedlen.c\
	ft_unsignedlen.c\
	ft_isint.c\
	ft_strsplit_free.c\
	ft_strsplit_len.c\
	ft_wcslen.c\
	ft_pow_int.c\
	ft_atoi32.c
LIBFT_SOURCES = $(addprefix $(LIBFT_SOURCES_DIRECTORY), $(LIBFT_SOURCES_LIST))

# LIBFT_OBJECTS

LIBFT_OBJECTS_DIRECTORY = $(LIBFT_DIRECTORY)objects/
LIBFT_OBJECTS_LIST = $(patsubst %.c, %.o, $(LIBFT_SOURCES_LIST))
LIBFT_OBJECTS = $(addprefix $(LIBFT_OBJECTS_DIRECTORY), $(LIBFT_OBJECTS_LIST))

# HEADERS

HEADERS_LIST = \
	ft_printf.h\
	ft_printf_lib.h
HEADERS_DIRECTORY = ./includes/
HEADERS = $(addprefix $(HEADERS_DIRECTORY), $(HEADERS_LIST))

# SOURCES

SOURCES_DIRECTORY = ./sources/
SOURCES_LIST = \
	ft_printf.c\
	ft_vprintf.c\
	ft_dprintf.c\
	ft_vdprintf.c\
	parse.c\
	parse_placeholder.c\
	part.c\
	handle_type.c\
	handle_d.c\
	handle_u.c\
	handle_o.c\
	handle_x.c\
	handle_b.c\
	handle_p.c\
	handle_c.c\
	handle_wc.c\
	handle_percent.c\
	handle_s.c\
	handle_ws.c\
	handle_n.c\
	handle_inv_type.c\
	strcatunbr_ptr.c\
	strcat_ptr.c\
	strncat_ptr.c\
	strcatwchar_ptr.c\
	utils.c
SOURCES = $(addprefix $(SOURCES_DIRECTORY), $(SOURCES_LIST))

# OBJECTS

OBJECTS_DIRECTORY = objects/
OBJECTS_LIST = $(patsubst %.c, %.o, $(SOURCES_LIST))
OBJECTS	= $(addprefix $(OBJECTS_DIRECTORY), $(OBJECTS_LIST))

# COLORS

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(LIBFT) $(LIBFT_OBJECTS) $(OBJECTS_DIRECTORY) $(OBJECTS)
	@ar rc $(NAME) $(OBJECTS) $(LIBFT_OBJECTS)
	@ranlib $(NAME)
	@echo "\n$(NAME): $(GREEN)object files were created$(RESET)"
	@echo "$(NAME): $(GREEN)$(NAME) was created$(RESET)"

$(OBJECTS_DIRECTORY):
	@mkdir -p $(OBJECTS_DIRECTORY)
	@echo "$(NAME): $(GREEN)$(OBJECTS_DIRECTORY) was created$(RESET)"

$(OBJECTS_DIRECTORY)%.o : $(SOURCES_DIRECTORY)%.c $(HEADERS)
	@$(CC) $(FLAGS) -c $(INCLUDES) $< -o $@
	@echo "$(GREEN).$(RESET)\c"

$(LIBFT):
	@echo "$(NAME): $(GREEN)Creating $(LIBFT)...$(RESET)"
	@$(MAKE) -sC $(LIBFT_DIRECTORY)

clean:
	@$(MAKE) -sC $(LIBFT_DIRECTORY) clean
	@rm -rf $(OBJECTS_DIRECTORY)
	@echo "$(NAME): $(RED)$(OBJECTS_DIRECTORY) was deleted$(RESET)"
	@echo "$(NAME): $(RED)object files were deleted$(RESET)"

fclean: clean
	@rm -f $(LIBFT)
	@echo "$(NAME): $(RED)$(LIBFT) was deleted$(RESET)"
	@rm -f $(NAME)
	@echo "$(NAME): $(RED)$(NAME) was deleted$(RESET)"

re:
	@$(MAKE) fclean
	@$(MAKE) all

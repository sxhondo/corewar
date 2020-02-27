# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ylila <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/11 03:31:44 by ylila             #+#    #+#              #
#    Updated: 2019/08/11 03:31:47 by ylila            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

FLAGS = -Wall -Wextra -Werror

SRCS = ft_strlen.c ft_strcmp.c ft_strncmp.c ft_strcpy.c ft_strncpy.c \
	ft_strcat.c ft_strncat.c ft_strlcat.c ft_strstr.c ft_strnstr.c \
	ft_strchr.c ft_strrchr.c ft_isalpha.c ft_isdigit.c ft_isalnum.c \
	ft_isascii.c ft_isprint.c ft_toupper.c ft_isupper.c ft_islower.c \
	ft_tolower.c ft_strdup.c ft_atoi.c ft_memset.c ft_bzero.c ft_memcpy.c \
	ft_memccpy.c ft_memmove.c ft_memchr.c ft_memcmp.c ft_memalloc.c \
	ft_memdel.c ft_strnew.c ft_strdel.c ft_strclr.c ft_striter.c \
	ft_striteri.c ft_strmap.c ft_strmapi.c ft_strequ.c ft_strnequ.c \
	ft_strsub.c ft_strjoin.c ft_strtrim.c ft_strsplit.c ft_itoa.c ft_putchar.c \
	ft_putstr.c ft_putendl.c ft_putnbr.c ft_putchar_fd.c ft_putstr_fd.c \
	ft_putendl_fd.c ft_putnbr_fd.c ft_lstnew.c ft_lstdelone.c ft_lstdel.c \
	ft_lstadd.c ft_lstiter.c ft_lstpush.c ft_pow.c ft_fib.c ft_sqrt.c \
	ft_len_num.c ft_reverse.c ft_round.c ft_floor.c ft_ceil.c ft_atol.c \
	get_next_line.c

OBJECTS = $(SRCS:.c=.o)

INCLUDE = ./

all: $(NAME)

$(NAME):
	@gcc -c $(SRCS) $(FLAGS) -I$(INCLUDE) -O3
	@ar rc $(NAME) $(OBJECTS)
	@ranlib $(NAME)

clean:
	@rm -f $(OBJECTS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_lib.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazhni <vbrazhni@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 23:23:12 by vbrazhni          #+#    #+#             */
/*   Updated: 2018/10/27 23:23:12 by vbrazhni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_LIB_H

# define FT_PRINTF_LIB_H

# include "libft.h"
# include <stdarg.h>
# include <inttypes.h>
# include <unistd.h>
# include <stdlib.h>
# include <wchar.h>

/*
** Part
*/

typedef struct		s_part
{
	char			*content;
	size_t			size;
	struct s_part	*next;
}					t_part;

/*
** %[flags][width][.precision][length]type
*/

/*
** Flag
*/

/*
** Codes
*/

# define MINUS			0b000000001
# define PLUS			0b000000010
# define SPACE			0b000000100
# define HASH			0b000001000
# define ZERO			0b000010000
# define APOSTROPHE		0b000100000
# define UPPER			0b001000000

/*
** Data type
*/

typedef struct		s_flag
{
	char			flag;
	int				code;
}					t_flag;

/*
** Flag — Code
*/

static t_flag		g_flag[] =
{
	{
		.flag = '-',
		.code = MINUS
	},
	{
		.flag = '+',
		.code = PLUS
	},
	{
		.flag = ' ',
		.code = SPACE
	},
	{
		.flag = '#',
		.code = HASH
	},
	{
		.flag = '0',
		.code = ZERO
	},
	{
		.flag = '\'',
		.code = APOSTROPHE
	}
};

/*
** Length
*/

/*
** Codes
*/

# define LENGTH_L		1
# define LENGTH_LL		2
# define LENGTH_H		3
# define LENGTH_HH		4
# define LENGTH_J		5
# define LENGTH_Z		6
# define LENGTH_BIG_L	7
# define LENGTH_T		8

/*
** Placeholder
*/

typedef struct		s_placeholder
{
	uint8_t			flags;
	int				width;
	int				precision;
	uint8_t			length;
	char			type;
	int				padding;
	uint8_t			base;

}					t_placeholder;

/*
** Type
*/

typedef struct		s_type
{
	char			type;
	char			*(*function)(t_placeholder* placeholder, va_list args);
}					t_type;

/*
** Functions
*/

int					handle_type(t_placeholder *ph, va_list args,
								int *size, t_part **list);

char				*handle_d(t_placeholder *ph, va_list args);

char				*handle_u(t_placeholder *ph, va_list args);

char				*handle_o(t_placeholder *ph, va_list args);

char				*handle_x(t_placeholder *ph, va_list args);

char				*handle_b(t_placeholder *ph, va_list args);

char				*handle_p(t_placeholder *ph, va_list args);

char				*handle_c(t_placeholder *ph, va_list args);

char				*handle_wc(t_placeholder *ph, va_list args);

char				*handle_percent(t_placeholder *ph, va_list args);

char				*handle_s(t_placeholder *ph, va_list args);

char				*handle_ws(t_placeholder *ph, va_list args);

char				*handle_n(t_placeholder *ph, va_list args);

char				*handle_inv_type(t_placeholder *ph);

/*
** Type — Function
*/

static t_type		g_type[] =
{
	{'d', &handle_d},
	{'i', &handle_d},
	{'u', &handle_u},
	{'o', &handle_o},
	{'x', &handle_x},
	{'b', &handle_b},
	{'p', &handle_p},
	{'c', &handle_c},
	{'C', &handle_wc},
	{'%', &handle_percent},
	{'s', &handle_s},
	{'S', &handle_ws},
	{'n', &handle_n}
};

/*
** Color
*/

/*
** Type
*/

typedef struct		s_color
{
	char			*color;
	char			*code;
}					t_color;

/*
** Color — Code
*/

static t_color		g_color[] =
{
	{
		.color = "{RED}",
		.code = "\x1b[31m"
	},
	{
		.color = "{GREEN}",
		.code = "\x1b[32m"
	},
	{
		.color = "{YELLOW}",
		.code = "\x1b[33m"
	},
	{
		.color = "{BLUE}",
		.code = "\x1b[34m"
	},
	{
		.color = "{MAGENDA}",
		.code = "\x1b[35m"
	},
	{
		.color = "{CYAN}",
		.code = "\x1b[36m"
	},
	{
		.color = "{RESET}",
		.code = "\x1b[0m"
	}
};

/*
** Functions
*/

/*
** Parse
*/

t_part				*parse(int *size, char *ptr, va_list args);

void				parse_flags(uint8_t *flags, char **ptr);

void				parse_width(t_placeholder *ph, char **ptr, va_list args);

void				parse_precision(int *precision, char **ptr, va_list args);

void				parse_length(uint8_t *length, char **ptr);

void				parse_type(t_placeholder *ph, char type);

/*
** Part
*/

t_part				*create_part(char *str, size_t size);

void				add_part(t_part **list, t_part *new);

char				*parts_to_str(t_part *list, int len);

void				parts_free(t_part **list);

/*
** Arguments
*/

uintmax_t			get_unsigned(t_placeholder *ph, va_list args);

/*
** Additional functions
*/

void				strcatunbr_ptr(t_placeholder *ph, uintmax_t num,
									char **str);

void				strcat_ptr(char **dest, char *src);

void				strncat_ptr(char **dest, const char *src, size_t n);

void				strcatwchar_ptr(char **str, wchar_t c);

/*
** Utils
*/

size_t				sep_num(uintmax_t num);

unsigned int		get_base(char c);

char				*get_prefix(int base, int flags);

int					wchar_size(wchar_t c);

size_t				wstr_size(wchar_t *s);

#endif

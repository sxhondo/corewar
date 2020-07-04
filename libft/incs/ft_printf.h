/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 16:34:24 by sxhondo           #+#    #+#             */
/*   Updated: 2019/09/23 16:45:52 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_FT_PRINTF_H
# define FT_PRINTF_FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>

# define ZERO		1u
# define PLUS		4u
# define SPACE		8u
# define LEFT		16u
# define CASE		32u
# define SHARP		64u

/*
** CHAR == 'hh'
** SHORT == 'h'
** LONG == 'l'
** LONG_LONG == 'll'
** LLONG == 'L'
*/

# define CHAR		1u
# define SHORT		2u
# define LONG		8u
# define LONG_LONG	16u
# define LLONG		32u

typedef struct		s_num
{
	uint64_t		num;
	unsigned int	prec;
	char			sign;
	unsigned int	nblen;
	int				exp;
}					t_num;

typedef struct		s_fmt
{
	unsigned int	flags;
	int				width;
	unsigned int	lmodifier;
	int				precision;
	unsigned int	base;
	const char		*iter;
}					t_fmt;

/*
** processings
*/

int					process_precision(t_fmt *fmt, va_list args);
int					process_width(t_fmt *fmt, va_list args);
unsigned int		process_flags(t_fmt *fmt);
unsigned int		process_lmodifier(t_fmt *fmt);
unsigned int		process_base(t_fmt	*fmt);

/*
** conversions
*/

int					get_percent(t_fmt *fmt, t_vec *buf);
int					get_str(t_fmt *fmt, va_list args, t_vec *buf);
void				get_ptr(t_fmt *fmt, va_list args, t_vec *buf);
int					get_char(t_fmt *fmt, va_list args, t_vec *buf);
int					get_num(int64_t num, t_fmt *fmt, t_vec *buf, int sig);
int					get_dnum(long double dnum, t_fmt *fmt, t_vec *buf);

/*
** num - utilities
*/

unsigned int		pf_itoa_base(uint64_t num, char s[], unsigned base,
																	int sig);
void				handle_negative(t_fmt *fmt, int64_t num);
void				apply_upcase(char *tmp);
char				get_sign(t_fmt *fmt, t_vec *buf, int64_t num, int sig);
int					recount_nblen(t_fmt *fmt, int64_t num);

/*
** dnum - utilities
*/

long double			roundd(long double dnum);
char				get_dsign(long double dnum, t_fmt *fmt);
int					put_zero(t_fmt *fmt, unsigned char *p);
long double			get_exp(long double dnum, t_num *num);
void				put_exp(char *exp, t_num *num);

/*
** expand argument
*/

void				pcsp(t_fmt	*fmt, va_list args, t_vec *buf);
void				positive_negative_nums(t_fmt *fmt, va_list args,
																t_vec *buf);
void				positive_nums(t_fmt *fmt, va_list args, t_vec *buf);
void				floats(t_fmt *fmt, va_list args, t_vec *buf);

/*
** process utilities
*/

int					skip_atoi(const char *s);
int					ft_isspecial(char ch);

/*
** some bonuses
*/

void				print_non_printable(t_fmt *fmt, va_list args, t_vec *buf);
void				get_color(t_fmt *fmt, t_vec *buf);
void				put_nonp_in_buf(t_fmt *fmt, t_vec *buf, const char *str,
															unsigned lcpy);
int					ft_printf(const char *format, ...);
int					ft_fprintf(int fd, const char *restrict format, ...);
int					ft_vfprintf(int fd, const char *fmt, va_list args);

#endif

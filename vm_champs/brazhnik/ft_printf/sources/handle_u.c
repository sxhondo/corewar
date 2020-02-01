/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_u.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazhni <vbrazhni@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 11:42:33 by vbrazhni          #+#    #+#             */
/*   Updated: 2018/11/04 11:42:33 by vbrazhni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_lib.h"
#include <locale.h>

uintmax_t	get_unsigned(t_placeholder *ph, va_list args)
{
	uintmax_t num;

	if (ph->type == 'p')
		num = (uintmax_t)va_arg(args, void *);
	else if (ph->length == LENGTH_H)
		num = (uintmax_t)((unsigned short int)va_arg(args, unsigned int));
	else if (ph->length == LENGTH_HH)
		num = (uintmax_t)((unsigned char)va_arg(args, unsigned int));
	else if (ph->length == LENGTH_L)
		num = (uintmax_t)va_arg(args, unsigned long int);
	else if (ph->length == LENGTH_LL)
		num = (uintmax_t)va_arg(args, unsigned long long int);
	else if (ph->length == LENGTH_Z)
		num = (uintmax_t)va_arg(args, size_t);
	else if (ph->length == LENGTH_T)
		num = (uintmax_t)va_arg(args, size_t);
	else if (ph->length == LENGTH_J)
		num = va_arg(args, uintmax_t);
	else
		num = (uintmax_t)va_arg(args, unsigned int);
	return (num);
}

static void	update_placeholder(t_placeholder *ph, uintmax_t num)
{
	size_t	numlen;
	size_t	seplen;

	ph->flags &= ~SPACE;
	ph->flags &= ~PLUS;
	ph->flags &= ~HASH;
	if (ph->flags & MINUS || ph->precision != -1)
		ph->flags &= ~ZERO;
	numlen = 0;
	if (num || ph->precision)
		numlen = ft_unsignedlen(num, ph->base);
	seplen = 0;
	if (ph->flags & APOSTROPHE)
		seplen = sep_num(num) * ft_strlen(localeconv()->thousands_sep);
	ph->precision = FT_MAX(ph->precision, (int)(numlen + seplen));
	ph->width = FT_MAX(ph->width, ph->precision);
	ph->padding = ph->width - ph->precision;
}

char		*handle_u(t_placeholder *ph, va_list args)
{
	uintmax_t	num;
	char		*str;

	update_placeholder(ph, (num = get_unsigned(ph, args)));
	if (!(str = ft_strnew(ph->width)))
		exit(1);
	if (!(ph->flags & MINUS) && !(ph->flags & ZERO))
		while (ph->padding > 0 && ph->padding--)
			*str++ = ' ';
	if (ph->precision)
		strcatunbr_ptr(ph, num, &str);
	if (ph->flags & MINUS)
		while (ph->padding > 0 && ph->padding--)
			*str++ = ' ';
	return (str - ph->width);
}

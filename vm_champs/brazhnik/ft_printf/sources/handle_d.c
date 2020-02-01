/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazhni <vbrazhni@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 11:42:23 by vbrazhni          #+#    #+#             */
/*   Updated: 2018/11/04 11:42:24 by vbrazhni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_lib.h"
#include <locale.h>
#include <stddef.h>

static intmax_t	get_signed(t_placeholder *ph, va_list args)
{
	intmax_t num;

	if (ph->length == LENGTH_H)
		num = (intmax_t)((short int)va_arg(args, int));
	else if (ph->length == LENGTH_HH)
		num = (intmax_t)((signed char)va_arg(args, int));
	else if (ph->length == LENGTH_L)
		num = (intmax_t)va_arg(args, long int);
	else if (ph->length == LENGTH_LL)
		num = (intmax_t)va_arg(args, long long int);
	else if (ph->length == LENGTH_Z)
		num = (intmax_t)va_arg(args, ssize_t);
	else if (ph->length == LENGTH_T)
		num = (intmax_t)va_arg(args, ptrdiff_t);
	else if (ph->length == LENGTH_J)
		num = va_arg(args, intmax_t);
	else
		num = (intmax_t)va_arg(args, int);
	return (num);
}

static void		update_placeholder(t_placeholder *ph, intmax_t num)
{
	size_t	unumlen;
	size_t	seplen;
	t_bool	has_sign;

	ph->flags &= ~HASH;
	if (ph->flags & MINUS || ph->precision != -1)
		ph->flags &= ~ZERO;
	if (num < 0)
		ph->flags &= ~(PLUS + SPACE);
	if (ph->flags & PLUS)
		ph->flags &= ~SPACE;
	unumlen = 0;
	if (num || ph->precision)
		unumlen = ft_unsignedlen(FT_ABS(num), ph->base);
	seplen = 0;
	if (ph->flags & APOSTROPHE)
		seplen = sep_num(FT_ABS(num)) * ft_strlen(localeconv()->thousands_sep);
	has_sign = ((ph->flags & PLUS) || (ph->flags & SPACE) || num < 0);
	ph->precision = FT_MAX(ph->precision, (int)(unumlen + seplen));
	ph->width = FT_MAX(ph->width, ph->precision + ((has_sign) ? 1 : 0));
	ph->padding = ph->width - (ph->precision + ((has_sign) ? 1 : 0));
}

char			*handle_d(t_placeholder *ph, va_list args)
{
	intmax_t	num;
	char		*str;

	update_placeholder(ph, (num = get_signed(ph, args)));
	if (!(str = ft_strnew(ph->width)))
		exit(1);
	if (!(ph->flags & MINUS) && !(ph->flags & ZERO))
		while (ph->padding > 0 && ph->padding--)
			*str++ = ' ';
	if (num < 0)
		*str++ = '-';
	else if (ph->flags & PLUS)
		*str++ = '+';
	else if (ph->flags & SPACE)
		*str++ = ' ';
	if (ph->precision)
		strcatunbr_ptr(ph, (uintmax_t)FT_ABS(num), &str);
	if (ph->flags & MINUS)
		while (ph->padding > 0 && ph->padding--)
			*str++ = ' ';
	return (str - ph->width);
}

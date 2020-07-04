/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processings.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 20:21:55 by sxhondo           #+#    #+#             */
/*   Updated: 2019/08/21 20:21:57 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_printf.h"

unsigned		process_flags(t_fmt *fmt)
{
	unsigned	flags;

	flags = 0;
	while (*fmt->iter++ && ft_isspecial(*fmt->iter))
	{
		if (*fmt->iter == '-' && (flags |= LEFT))
			continue;
		if (*fmt->iter == '+' && (flags |= PLUS))
			continue;
		if (*fmt->iter == ' ' && (flags |= SPACE))
			continue;
		if (*fmt->iter == '#' && (flags |= SHARP))
			continue;
		if (*fmt->iter == '0' && (flags |= ZERO))
			continue;
	}
	return (flags);
}

int				process_width(t_fmt *fmt, va_list args)
{
	int			width;

	width = -1;
	if (*fmt->iter == '*')
	{
		++fmt->iter;
		if (!(width = va_arg(args, int)))
			width = -1;
	}
	if (ft_isdigit(*fmt->iter))
	{
		width = skip_atoi(fmt->iter);
		fmt->iter += ft_nblen(width);
	}
	return (width);
}

int				process_precision(t_fmt *fmt, va_list args)
{
	int			precision;

	precision = -1;
	if (*fmt->iter == '.')
	{
		fmt->iter++;
		precision++;
	}
	if (ft_isdigit(*fmt->iter))
	{
		precision = skip_atoi(fmt->iter);
		fmt->iter += ft_nblen(precision);
	}
	else if (*fmt->iter == '*')
	{
		fmt->iter++;
		precision = va_arg(args, int);
	}
	return (precision);
}

unsigned		process_lmodifier(t_fmt *fmt)
{
	unsigned	lmodifier;

	lmodifier = 0;
	if (*fmt->iter == 'h')
		lmodifier |= (*++fmt->iter == 'h') ? CHAR : SHORT;
	else if (*fmt->iter == 'l')
		lmodifier |= (*++fmt->iter == 'l') ? LONG_LONG : LONG;
	else if (*fmt->iter == 'L')
		lmodifier |= LLONG;
	fmt->iter += (lmodifier & CHAR || lmodifier & LLONG) ||
			lmodifier & LONG_LONG ? 1 : 0;
	return (lmodifier);
}

unsigned		process_base(t_fmt *fmt)
{
	unsigned	base;

	base = 10;
	if (*fmt->iter == 'o')
		base = 8;
	else if (*fmt->iter == 'x' || *fmt->iter == 'X')
	{
		if (*fmt->iter == 'X')
			fmt->flags |= CASE;
		base = 16;
	}
	else if (*fmt->iter == 'b')
		base = 2;
	return (base);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ws.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazhni <vbrazhni@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 11:44:08 by vbrazhni          #+#    #+#             */
/*   Updated: 2018/11/04 11:44:08 by vbrazhni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_lib.h"

size_t		get_ws_precision(wchar_t *s, int precision)
{
	size_t	size;

	size = 0;
	while (*s && (int)(size + wchar_size(*s)) <= precision)
		size += wchar_size(*s++);
	return (size);
}

t_bool		has_locale(t_placeholder *ph, wchar_t *s)
{
	int		i;

	i = 0;
	while ((i += wchar_size(*s)) <= ph->precision)
	{
		if ((wchar_size(*s) > 1 && MB_CUR_MAX == 1) || (wchar_size(*s) == 0))
			return (false);
		s++;
	}
	return (true);
}

static void	update_placeholder(t_placeholder *ph, wchar_t *s)
{
	if (ph->flags & MINUS)
		ph->flags &= ~ZERO;
	ph->precision = (ph->precision == -1 ||
		wstr_size(s) < get_ws_precision(s, ph->precision)) ?
					wstr_size(s) : get_ws_precision(s, ph->precision);
	ph->width = FT_MAX(ph->width, ph->precision);
	ph->padding = ph->width - ph->precision;
	if (!has_locale(ph, s))
		ph->width = -1;
}

char		*handle_ws(t_placeholder *ph, va_list args)
{
	wchar_t	*s;
	char	c;
	int		i;
	char	*str;

	if (!(s = va_arg(args, wchar_t *)))
		s = L"(null)";
	update_placeholder(ph, s);
	if (ph->width == -1)
		return (NULL);
	if (!(str = ft_strnew(ph->width)))
		exit(1);
	c = (ph->flags & ZERO) ? '0' : ' ';
	if (!(ph->flags & MINUS))
		while (ph->padding > 0 && ph->padding--)
			*str++ = c;
	i = 0;
	while ((i += wchar_size(*s)) <= ph->precision)
		if (*s > FT_UCHAR_MAX || (MB_CUR_MAX != 1 && *s < FT_UCHAR_MAX))
			strcatwchar_ptr(&str, *s++);
		else
			*str++ = (char)*s++;
	while (ph->padding > 0 && ph->padding--)
		*str++ = c;
	return (str - ph->width);
}

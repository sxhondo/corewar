/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_s.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazhni <vbrazhni@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 11:43:56 by vbrazhni          #+#    #+#             */
/*   Updated: 2018/11/04 11:43:57 by vbrazhni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_lib.h"

static void	update_placeholder(t_placeholder *ph, char *s)
{
	if (ph->flags & MINUS)
		ph->flags &= ~ZERO;
	ph->precision =
		(ph->precision == -1 || (int)ft_strlen(s) < ph->precision) ?
							(int)ft_strlen(s) : ph->precision;
	ph->width = FT_MAX(ph->width, ph->precision);
	ph->padding = ph->width - ph->precision;
}

char		*handle_s(t_placeholder *ph, va_list args)
{
	char	c;
	char	*s;
	char	*str;

	if (!(s = va_arg(args, char*)))
		s = "(null)";
	update_placeholder(ph, s);
	if (!(str = ft_strnew(ph->width)))
		exit(1);
	c = (ph->flags & ZERO) ? '0' : ' ';
	if (!(ph->flags & MINUS))
		while (ph->padding > 0 && ph->padding--)
			*str++ = c;
	strncat_ptr(&str, s, (size_t)ph->precision);
	while (ph->padding > 0 && ph->padding--)
		*str++ = c;
	return (str - ph->width);
}

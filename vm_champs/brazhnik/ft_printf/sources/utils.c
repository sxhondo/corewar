/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazhni <vbrazhni@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 16:48:41 by vbrazhni          #+#    #+#             */
/*   Updated: 2018/11/01 16:48:42 by vbrazhni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_lib.h"

size_t		sep_num(uintmax_t num)
{
	size_t	numlen;

	numlen = ft_unsignedlen(num, 10);
	return ((numlen / 3) - ((numlen && !(numlen % 3)) ? 1 : 0));
}

unsigned	get_base(char c)
{
	if (c == 'b')
		return (2);
	else if (c == 'o')
		return (8);
	else if (c == 'x' || c == 'p')
		return (16);
	else
		return (10);
}

char		*get_prefix(int base, int flags)
{
	if (base == 2)
		return ((flags & UPPER) ? "0B" : "0b");
	else if (base == 8)
		return ("0");
	else if (base == 16)
		return ((flags & UPPER) ? "0X" : "0x");
	else
		return ("");
}

int			wchar_size(wchar_t c)
{
	if (c < 0 & MB_CUR_MAX != 1)
		return (0);
	else if ((c <= 0x7F || (c <= FT_UCHAR_MAX && MB_CUR_MAX == 1)))
		return (1);
	else if (c <= 0x7FF)
		return (2);
	else if (c >= 0xD800 && c <= 0xDFFF)
		return (0);
	else if (c <= 0xFFFF)
		return (3);
	else if (c <= 0x10FFFF)
		return (4);
	else
		return (0);
}

size_t		wstr_size(wchar_t *s)
{
	size_t	size;

	size = 0;
	while (*s)
		size += wchar_size(*s++);
	return (size);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strcatwchar_ptr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazhni <vbrazhni@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/03 01:17:03 by vbrazhni          #+#    #+#             */
/*   Updated: 2018/11/03 01:17:03 by vbrazhni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_lib.h"

void	strcatwchar_ptr(char **str, wchar_t c)
{
	if (c <= 0x7F || (c <= FT_UCHAR_MAX && MB_CUR_MAX == 1))
		*(*str)++ = (char)c;
	else if (c <= 0x7FF)
	{
		*(*str)++ = (char)((c >> 6) + 0xC0);
		*(*str)++ = (char)((c & 0x3F) + 0x80);
	}
	else if (c <= 0xFFFF)
	{
		*(*str)++ = (char)((c >> 12) + 0xE0);
		*(*str)++ = (char)(((c >> 6) & 0x3F) + 0x80);
		*(*str)++ = (char)((c & 0x3F) + 0x80);
	}
	else if (c <= 0x10FFFF)
	{
		*(*str)++ = (char)((c >> 18) + 0xF0);
		*(*str)++ = (char)(((c >> 12) & 0x3F) + 0x80);
		*(*str)++ = (char)(((c >> 6) & 0x3F) + 0x80);
		*(*str)++ = (char)((c & 0x3F) + 0x80);
	}
}

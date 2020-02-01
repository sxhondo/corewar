/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strcatunbr_ptr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazhni <vbrazhni@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 19:27:57 by vbrazhni          #+#    #+#             */
/*   Updated: 2018/11/02 19:27:58 by vbrazhni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_lib.h"
#include <locale.h>

static void	strcatunbr_ptr_digit(t_placeholder *ph,
									uintmax_t digit,
									size_t *numlen,
									char **str)
{
	if (digit < 10)
		*(*str)++ = (char)(digit + '0');
	else
		*(*str)++ = (char)(((ph->flags & UPPER) ? 'A' : 'a') + (digit - 10));
	(*numlen)--;
	if ((ph->flags & APOSTROPHE) && *numlen && !(*numlen % 3))
		strcat_ptr(str, localeconv()->thousands_sep);
}

static void	strcatunbr_ptr_base(t_placeholder *ph,
									uintmax_t num,
									size_t *numlen,
									char **str)
{
	if (num)
	{
		strcatunbr_ptr_base(ph, num / get_base(ph->type), numlen, str);
		strcatunbr_ptr_digit(ph, num % get_base(ph->type), numlen, str);
	}
}

void		strcatunbr_ptr(t_placeholder *ph, uintmax_t num, char **str)
{
	size_t	numlen;
	size_t	seplen;

	numlen = ft_unsignedlen(num, get_base(ph->type));
	seplen = (ph->flags & APOSTROPHE) ?
		sep_num(FT_ABS(num)) * ft_strlen(localeconv()->thousands_sep) : 0;
	if (ph->flags & ZERO)
		while (ph->padding > 0 && ph->padding--)
			*(*str)++ = '0';
	while (ph->precision > (int)(numlen + seplen) && ph->precision--)
		*(*str)++ = '0';
	if (num)
		strcatunbr_ptr_base(ph, num, &numlen, str);
	else
		*(*str)++ = '0';
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 16:02:54 by sxhondo           #+#    #+#             */
/*   Updated: 2019/09/24 16:02:55 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned				itoa_base(uint64_t num, char s[], unsigned base)
{
	const char			hex_table[17] = "0123456789abcdef";
	uint64_t			rmndr;
	uint64_t			save;
	char				*ptr;

	ptr = s;
	save = base + 1;
	if ((int64_t)num < 0)
		num = -num;
	if (base < 2 || base > 16)
		return (0);
	while (save >= base)
	{
		rmndr = num / base;
		save = rmndr * base;
		if (base <= 10)
			*ptr++ = (char)((num - save) % 10 | 0x30u);
		if (base > 10)
			*ptr++ = hex_table[num - save];
		num = rmndr;
	}
	*ptr = '\0';
	ft_strrev(s);
	return ((unsigned)(ptr - s));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 16:19:02 by sxhondo           #+#    #+#             */
/*   Updated: 2019/09/15 16:19:06 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_printf.h"

unsigned int			pf_itoa_base(uint64_t num, char s[],
														unsigned base, int sig)
{
	const char			hex_table[17] = "0123456789abcdef";
	uint64_t			rmndr;
	uint64_t			save;
	char				*ptr;

	ptr = s;
	save = base + 1;
	if (sig == 1 && (int64_t)num < 0)
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
	return ((unsigned int)(ptr - s));
}

char					get_sign(t_fmt *fmt, t_vec *buf, int64_t num, int sig)
{
	char				sign;

	sign = 0;
	if (fmt->flags & PLUS && num != UINT32_MAX)
		sign = num < 0 ? '-' : '+';
	else if (num < 0 && sig == 1)
		sign = '-';
	else if (fmt->flags & SPACE)
		sign = ' ';
	if (fmt->flags & ZERO && sign)
	{
		ft_vec_add(&buf, &sign);
		fmt->width--;
		sign = 0;
		return (sign);
	}
	return (sign);
}

int						recount_nblen(t_fmt *fmt, int64_t num)
{
	int					i;

	i = 0;
	if (fmt->base == 10)
		i++;
	if (fmt->flags & SHARP && fmt->base != 10 && num != 0)
	{
		i++;
		if (fmt->base & 16u)
			i++;
	}
	return (i);
}

void					handle_negative(t_fmt *fmt, int64_t num)
{
	if (fmt->width < -1 && num != 0)
	{
		fmt->width = -fmt->width;
		fmt->flags |= LEFT;
	}
}

void					apply_upcase(char *tmp)
{
	while (*tmp)
	{
		if (*tmp >= 'a' && *tmp <= 'z')
			*tmp -= 32;
		tmp++;
	}
}

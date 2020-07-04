/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dnum_utilities.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 17:09:47 by sxhondo           #+#    #+#             */
/*   Updated: 2019/09/15 17:09:49 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_printf.h"

long double						roundd(long double dnum)
{
	long double					tmp;

	tmp = (uint64_t)(dnum * 100 + .5);
	return (tmp / 100);
}

long double						get_exp(long double dnum, t_num *num)
{
	long double					save;

	save = dnum;
	if (!dnum)
		return (0);
	while ((uint64_t)save >= 9)
	{
		save /= 10;
		num->exp++;
	}
	while ((uint64_t)save == 0)
	{
		save *= 10;
		num->exp--;
	}
	return (save);
}

char							get_dsign(long double dnum, t_fmt *fmt)
{
	char						sign;

	sign = 0;
	if (fmt->flags & PLUS)
		sign = dnum < 0 ? '-' : '+';
	else if (dnum < 0)
		sign = '-';
	else if (fmt->flags & SPACE)
		sign = ' ';
	return (sign);
}

int								put_zero(t_fmt *fmt, unsigned char *p)
{
	int							i;

	*p++ = '0';
	i = 1;
	if (fmt->precision > 0 || fmt->flags & SHARP)
	{
		*p++ = '.';
		i++;
	}
	return (i);
}

void							put_exp(char *exp, t_num *num)
{
	char						tmp[99];
	char						*p_tmp;

	p_tmp = exp;
	if (num->exp < 0 && (num->exp = -num->exp))
		*p_tmp++ = '-';
	else
		*p_tmp++ = '+';
	if (num->exp < 10)
	{
		*p_tmp++ = '0';
		*p_tmp++ = (char)(num->exp + 0x30);
	}
	p_tmp = tmp;
	if (num->exp >= 10)
	{
		while (num->exp > 0)
		{
			*p_tmp++ = (char)(num->exp % 10 + 0x30);
			num->exp /= 10;
		}
		ft_strrev(tmp);
		ft_strcat(exp, tmp);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_module.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 16:37:57 by sxhondo           #+#    #+#             */
/*   Updated: 2019/08/29 16:37:59 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_printf.h"

unsigned int					print_dnum(t_fmt *fmt, t_vec *buf, t_num *num,
															unsigned char *dig)
{
	char						*p_exp;
	char						exp[99];
	unsigned int				nblen;
	unsigned char				e;

	fmt->flags &= ~ZERO;
	nblen = num->nblen;
	p_exp = exp;
	if (num->sign && num->nblen--)
		ft_vec_add(&buf, &num->sign);
	while (num->nblen--)
		ft_vec_add(&buf, &*dig++);
	if (*fmt->iter == 'e' || *fmt->iter == 'E')
	{
		e = fmt->flags & CASE ? 'E' : 'e';
		put_exp(p_exp, num);
		ft_vec_add(&buf, &e);
		while (*p_exp)
			ft_vec_add(&buf, &*p_exp++);
	}
	return (nblen);
}

int								write_dnum(t_fmt *fmt, long double dnum,
													unsigned char *ptr, int i)
{
	uint64_t					tmp;
	unsigned char				*p;

	p = ptr;
	while (i-- > 0)
	{
		tmp = roundd(dnum);
		*ptr++ = tmp | 0x30u;
		if (i == fmt->precision && (fmt->precision > 0 || fmt->flags & SHARP))
			*ptr++ = '.';
		dnum = dnum - (long double)tmp;
		dnum *= 10;
	}
	*ptr++ = '\0';
	return ((int)(ptr - p));
}

int								write_exp(t_fmt *fmt, long double dnum,
												t_num *num, unsigned char *p)
{
	int							i;
	uint64_t					tmp;
	unsigned char				*ptr;

	ptr = p;
	i = fmt->precision;
	dnum = get_exp(dnum, num);
	tmp = roundd(dnum);
	*ptr++ = tmp | 0x30u;
	*ptr++ = '.';
	dnum = dnum - (long double)tmp;
	dnum *= 10;
	while (i-- > 0)
	{
		tmp = roundd(dnum);
		*ptr++ = tmp | 0x30u;
		dnum = dnum - (long double)tmp;
		dnum *= 10;
	}
	fmt->width -= 4;
	*ptr++ = '\0';
	return ((int)(ptr - p - 1));
}

int								dtoa(long double dnum, unsigned char dig[],
														t_fmt *fmt, t_num *num)
{
	int							i;
	int							zero_tmblr;
	unsigned char				*ptr;
	unsigned char				*p;

	ptr = dig;
	p = dig;
	zero_tmblr = 0;
	i = fmt->precision;
	dnum = dnum < 0 ? -(dnum) : (dnum);
	if ((uint64_t)dnum == 0)
		zero_tmblr = put_zero(fmt, ptr);
	if (*fmt->iter == 'e' || *fmt->iter == 'E')
	{
		num->prec = i;
		return (write_exp(fmt, dnum, num, ptr));
	}
	while ((uint64_t)dnum > 0 && ++i)
		dnum /= 10;
	dnum *= 10;
	ptr += write_dnum(fmt, dnum, ptr + zero_tmblr, i);
	return ((int)(ptr - p) - 1 + zero_tmblr);
}

int								get_dnum(long double dnum, t_fmt *fmt,
																	t_vec *buf)
{
	unsigned char				digits[100];
	char						tmp;
	t_num						*num;

	if (!(num = ft_memalloc(sizeof(t_num))))
		return (0);
	fmt->precision = fmt->precision == -1 ? 6 : fmt->precision;
	num->nblen += dtoa(dnum, digits, fmt, num);
	if ((num->sign = get_dsign(dnum, fmt)))
		num->nblen++;
	num->nblen = fmt->flags & LEFT ? print_dnum(fmt, buf, num, digits) :
			num->nblen;
	tmp = fmt->flags & ZERO ? '0' : ' ';
	while (--fmt->width >= (int)num->nblen && fmt->width > -1)
		ft_vec_add(&buf, &tmp);
	if (!(fmt->flags & LEFT))
		print_dnum(fmt, buf, num, digits);
	fmt->iter += 1;
	free(num);
	return (0);
}

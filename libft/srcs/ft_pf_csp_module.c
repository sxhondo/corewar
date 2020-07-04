/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   csp_module.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 20:21:35 by sxhondo           #+#    #+#             */
/*   Updated: 2019/08/27 00:30:19 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_printf.h"

int						get_percent(t_fmt *fmt, t_vec *buf)
{
	char				tmp;
	char				per;

	per = '%';
	if (fmt->flags & LEFT)
		ft_vec_add(&buf, &per);
	tmp = fmt->flags & ZERO ? '0' : ' ';
	while (--fmt->width > 0)
		ft_vec_add(&buf, &tmp);
	if (!(fmt->flags & LEFT))
		ft_vec_add(&buf, &per);
	return (0);
}

int						get_char(t_fmt *fmt, va_list args, t_vec *buf)
{
	unsigned char		ch;
	char				tmp;

	tmp = ' ';
	ch = (unsigned char)va_arg(args, int);
	if (fmt->flags & LEFT)
		ft_vec_add(&buf, &ch);
	if (fmt->width < -1)
	{
		ft_vec_add(&buf, &ch);
		while (++fmt->width < -1)
			ft_vec_add(&buf, &tmp);
	}
	tmp = fmt->flags & ZERO ? '0' : ' ';
	while (--fmt->width > 0)
		ft_vec_add(&buf, &tmp);
	if (fmt->precision > -1)
		ft_vec_add(&buf, &ch);
	else if (!(fmt->flags & LEFT))
		ft_vec_add(&buf, &ch);
	return (0);
}

int						get_str(t_fmt *fmt, va_list args, t_vec *buf)
{
	const char			zero[] = "(null)";
	int					len;
	int					lcpy;
	const char			*str;
	char				tmp;

	if (!(str = va_arg(args, const char *)))
	{
		lcpy = 0;
		while (zero[lcpy])
			ft_vec_add(&buf, (void *)&zero[lcpy++]);
		return (0);
	}
	len = ft_strnlen(str, fmt->precision);
	lcpy = len;
	while (fmt->flags & LEFT && lcpy--)
		ft_vec_add(&buf, (void *)&*str++);
	tmp = fmt->flags & ZERO ? '0' : ' ';
	while (fmt->width > -1 && --fmt->width >= len)
		ft_vec_add(&buf, &tmp);
	while (len-- && lcpy > 0)
		ft_vec_add(&buf, (char *)str++);
	return (0);
}

static void				put_in_buf(t_fmt *fmt, t_vec *buf, int hexlen,
																char hex[])
{
	char				*prefix;
	char				*p;
	char				o;

	o = '0';
	p = hex;
	prefix = "0x";
	while (*prefix)
		ft_vec_add(&buf, &*prefix++);
	if (fmt->precision > -1)
		while (fmt->precision-- > hexlen)
			ft_vec_add(&buf, &o);
	while (*p)
		ft_vec_add(&buf, &*p++);
}

void					get_ptr(t_fmt *fmt, va_list args, t_vec *buf)
{
	int					hexlen;
	char				hex[15];
	uint64_t			pointer;
	int					prec;
	char				tmp;

	tmp = ' ';
	pointer = (uint64_t)va_arg(args, void *);
	hexlen = (int)pf_itoa_base(pointer, hex, 16, 0);
	prec = 0;
	if (fmt->precision == 0 && !(ft_strcmp(hex, "0")) && ++prec)
		ft_bzero(hex, 15);
	if (fmt->flags & LEFT)
		put_in_buf(fmt, buf, hexlen, hex);
	while (--fmt->width > hexlen + 1 && fmt->width > -1)
		ft_vec_add(&buf, &tmp);
	if (!(fmt->flags & LEFT))
		put_in_buf(fmt, buf, hexlen, hex);
}

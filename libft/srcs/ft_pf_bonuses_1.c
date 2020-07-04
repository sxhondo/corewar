/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   some_bonuses.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 19:23:37 by sxhondo           #+#    #+#             */
/*   Updated: 2019/11/01 19:57:17 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_printf.h"

void					print_non_printable(t_fmt *fmt, va_list args,
																	t_vec *buf)
{
	int					len;
	unsigned			lcpy;
	const char			*str;
	char				tmp;

	str = va_arg(args, const char *);
	len = ft_strnlen(str, fmt->precision);
	lcpy = len;
	if (fmt->flags & LEFT)
		put_nonp_in_buf(fmt, buf, str, lcpy);
	tmp = fmt->flags & ZERO ? '0' : ' ';
	while (--fmt->width >= len)
		ft_vec_add(&buf, &tmp);
	if (!(fmt->flags & LEFT))
		put_nonp_in_buf(fmt, buf, str, len);
	fmt->iter += 1;
}

int						get_valid_name(t_fmt *fmt, char *tab)
{
	const char			*str;
	int					i;

	i = 0;
	str = fmt->iter;
	str++;
	if (*str == 'B')
	{
		fmt->lmodifier |= 128u;
		str++;
	}
	while (*str && *str != '}')
	{
		if (*str == '%')
		{
			ft_bzero(tab, 7);
			return (0);
		}
		tab[i] = *str++;
		i++;
	}
	tab[i] = '\0';
	return (i);
}

static int				check_bold(t_fmt *fmt, char *tab, char *col)
{
	int		i;

	i = 0;
	if (fmt->lmodifier & 128u)
	{
		i++;
		fmt->lmodifier &= ~128u;
		if (!(ft_strcmp(tab, "yellow")))
			ft_memcpy(col, "[01;", 5);
		else
			ft_memcpy(col, "[1;", 4);
	}
	else if (ft_strcmp(tab, "eoc"))
		ft_memcpy(col, "[0;", 4);
	return (i);
}

int						put_col_in_buf(t_vec *buf, char *col)
{
	char				spec;

	spec = 0x1b;
	ft_vec_add(&buf, &spec);
	while (*col)
		ft_vec_add(&buf, &*col++);
	return (1);
}

void					get_color(t_fmt *fmt, t_vec *buf)
{
	char				tab[20];
	char				col[20];
	int					i;

	i = 0;
	i += get_valid_name(fmt, tab);
	i += check_bold(fmt, tab, col);
	if (!(ft_strcmp(tab, "red")))
		ft_strcat(col, "31m");
	else if (!(ft_strcmp(tab, "green")))
		ft_strcat(col, "32m");
	else if (!(ft_strcmp(tab, "yellow")))
		ft_strcat(col, "33m");
	else if (!(ft_strcmp(tab, "blue")))
		ft_strcat(col, "34m");
	else if (!(ft_strcmp(tab, "magenta")))
		ft_strcat(col, "35m");
	else if (!(ft_strcmp(tab, "cyan")))
		ft_strcat(col, "36m");
	else if (!(ft_strcmp(tab, "eoc")))
		ft_memcpy(col, "[0m", 4);
	if (i > 0 && put_col_in_buf(buf, col))
		fmt->iter += i + 2;
}

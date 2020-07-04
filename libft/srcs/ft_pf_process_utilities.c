/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pf_process_utilities.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 22:02:15 by sxhondo           #+#    #+#             */
/*   Updated: 2020/01/22 22:02:16 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_printf.h"

int				skip_atoi(const char *s)
{
	int			i;

	i = 0;
	while (ft_isdigit(*s))
		i = i * 10 + *s++ - '0';
	return (i);
}

int				ft_isspecial(char ch)
{
	if (ch == '*' || ch == '.' || ch == '%')
		return (0);
	if (ch >= ' ' && ch <= '0')
		return (1);
	return (0);
}

void			put_nonp_in_buf(t_fmt *fmt, t_vec *buf, const char *str,
									unsigned lcpy)
{
	char		ast;

	ast = '*';
	fmt->flags &= ~ZERO;
	while (*str && lcpy--)
	{
		if (*str < 33 || *str > 126)
			ft_vec_add(&buf, &ast);
		else
			ft_vec_add(&buf, (void *)&*str);
		str++;
	}
}

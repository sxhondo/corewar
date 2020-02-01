/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_inv_type.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazhni <vbrazhni@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 16:43:16 by vbrazhni          #+#    #+#             */
/*   Updated: 2018/11/04 16:43:17 by vbrazhni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_lib.h"

static void	update_placeholder(t_placeholder *ph)
{
	ph->width = FT_MAX(ph->width, 1);
	ph->padding = ph->width - 1;
}

char		*handle_inv_type(t_placeholder *ph)
{
	char c;
	char *str;

	update_placeholder(ph);
	if (!(str = ft_strnew(ph->width)))
		exit(1);
	c = (ph->flags & ZERO) ? '0' : ' ';
	if (!(ph->flags & MINUS))
		while (ph->padding > 0 && ph->padding--)
			*str++ = c;
	*str++ = ph->type;
	while (ph->padding > 0 && ph->padding--)
		*str++ = c;
	return (str - ph->width);
}

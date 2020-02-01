/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_p.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazhni <vbrazhni@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 11:43:33 by vbrazhni          #+#    #+#             */
/*   Updated: 2018/11/04 11:43:34 by vbrazhni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_lib.h"

static void	update_placeholder(t_placeholder *ph)
{
	ph->flags |= HASH;
}

char		*handle_p(t_placeholder *ph, va_list args)
{
	update_placeholder(ph);
	return (handle_x(ph, args));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazhni <vbrazhni@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 22:29:27 by vbrazhni          #+#    #+#             */
/*   Updated: 2018/10/30 22:29:28 by vbrazhni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_printf_lib.h"

int	ft_printf(const char *format, ...)
{
	int		size;
	va_list	args;

	va_start(args, format);
	size = ft_vdprintf(1, format, args);
	va_end(args);
	return (size);
}

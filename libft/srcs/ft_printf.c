/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 20:33:13 by sxhondo           #+#    #+#             */
/*   Updated: 2019/09/23 17:22:31 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_printf.h"

int							ft_fprintf(int fd, const char *restrict format, ...)
{
	va_list					args;
	int						done;

	if (!format)
		return (-1);
	va_start(args, format);
	done = ft_vfprintf(fd, format, args);
	va_end(args);
	return (done);
}

int							ft_printf(const char *restrict format, ...)
{
	va_list					args;
	int						done;

	if (!format)
		return (-1);
	va_start(args, format);
	done = ft_vfprintf(1, format, args);
	va_end(args);
	return (done);
}

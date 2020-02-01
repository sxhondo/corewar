/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vdprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazhni <vbrazhni@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 22:30:16 by vbrazhni          #+#    #+#             */
/*   Updated: 2018/10/30 22:30:16 by vbrazhni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_printf_lib.h"

int	ft_vdprintf(int fd, const char *format, va_list args)
{
	t_part	*list;
	int		size;
	char	*str;

	size = 0;
	list = parse(&size, (char *)format, args);
	if (size != -1)
	{
		str = parts_to_str(list, size);
		write(fd, str, size);
		free(str);
	}
	parts_free(&list);
	return (size);
}

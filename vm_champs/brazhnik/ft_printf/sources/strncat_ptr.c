/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strncat_ptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrazhni <vbrazhni@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 20:55:37 by vbrazhni          #+#    #+#             */
/*   Updated: 2018/11/02 20:55:37 by vbrazhni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_lib.h"

void	strncat_ptr(char **dest, const char *src, size_t n)
{
	while (n && *src)
	{
		*(*dest)++ = *src++;
		n--;
	}
}

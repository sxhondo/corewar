/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 22:03:27 by sxhondo           #+#    #+#             */
/*   Updated: 2020/01/22 22:03:27 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t			ft_strnlen(const char *str, size_t maxlen)
{
	size_t		len;

	len = 0;
	while (len < maxlen)
	{
		if (!*str)
			break ;
		str++;
		len++;
	}
	return (len);
}

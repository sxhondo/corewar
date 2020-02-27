/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylila <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 18:27:30 by ylila             #+#    #+#             */
/*   Updated: 2019/08/10 19:41:04 by mdeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*to;
	const char	*from;

	if (!dst && !src)
		return (NULL);
	to = (char *)dst;
	from = (const char *)src;
	if (from > to)
		while (len--)
			*to++ = *from++;
	else
	{
		from = from + len - 1;
		to = to + len - 1;
		while (len--)
			*to-- = *from--;
	}
	return (dst);
}

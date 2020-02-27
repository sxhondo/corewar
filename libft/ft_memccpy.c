/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylila <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 17:13:49 by ylila             #+#    #+#             */
/*   Updated: 2019/08/10 19:41:04 by mdeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*to;
	const unsigned char	*from;

	to = (unsigned char *)dst;
	from = (unsigned char *)src;
	while (n > 0 && *from != (unsigned char)c)
	{
		*to++ = *from++;
		--n;
	}
	if (n > 0)
	{
		*to++ = *from++;
		return ((void *)to);
	}
	return (NULL);
}

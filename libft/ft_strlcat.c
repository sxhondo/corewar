/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylila <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 16:33:51 by ylila             #+#    #+#             */
/*   Updated: 2019/08/10 19:41:04 by mdeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t dst_l;
	size_t src_l;

	dst_l = 0;
	src_l = 0;
	while (*dst)
	{
		++dst_l;
		++dst;
	}
	while (src[src_l])
		++src_l;
	if (size <= dst_l)
		src_l += size;
	else
		src_l += dst_l;
	while (*src && dst_l + 1 < size)
	{
		*dst++ = *src++;
		++dst_l;
	}
	*dst = '\0';
	return (src_l);
}

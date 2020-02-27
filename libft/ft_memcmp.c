/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylila <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 19:26:41 by ylila             #+#    #+#             */
/*   Updated: 2019/08/10 19:41:03 by mdeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	char			*str1;
	char			*str2;
	unsigned char	c1;
	unsigned char	c2;

	str1 = (char *)s1;
	str2 = (char *)s2;
	while (n--)
	{
		c1 = (unsigned char)*str1++;
		c2 = (unsigned char)*str2++;
		if (c1 != c2)
			return (c1 - c2);
	}
	return (0);
}

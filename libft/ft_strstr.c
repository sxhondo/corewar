/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylila <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 17:34:13 by ylila             #+#    #+#             */
/*   Updated: 2019/08/10 19:41:04 by mdeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>

char	*ft_strstr(const char *str, const char *to_find)
{
	const char	*haystack;
	const char	*needle;

	if (!(*to_find))
		return ((char*)str);
	while (*str)
	{
		if (*str == *to_find)
		{
			haystack = (const char*)str;
			needle = (const char*)to_find;
			while (*haystack++ == *needle++ && *needle)
				;
			if (!(*needle) && (*(haystack - 1) == *(needle - 1)))
				return ((char *)str);
		}
		++str;
	}
	return (NULL);
}

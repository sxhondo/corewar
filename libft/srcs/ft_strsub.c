/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 20:55:03 by sxhondo           #+#    #+#             */
/*   Updated: 2019/05/04 13:50:41 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t		i;
	char		*istr;
	int			t;

	t = (int)len;
	i = 0;
	if (s == NULL || t < 0)
		return (NULL);
	istr = ft_memalloc(len + 1);
	if (!istr)
		return (NULL);
	while (i < len)
	{
		istr[i] = s[start + i];
		i++;
	}
	istr[i] = '\0';
	return (istr);
}

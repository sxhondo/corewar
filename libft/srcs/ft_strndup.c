/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 18:44:27 by sxhondo           #+#    #+#             */
/*   Updated: 2019/04/24 18:53:25 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	size_t	i;
	char	*istr;

	i = ft_strlen(s1);
	istr = ft_memalloc(sizeof(*istr) * n + 1);
	if (!istr)
		return (NULL);
	i = 0;
	while (s1[i] && i < n)
	{
		istr[i] = s1[i];
		i++;
	}
	istr[i] = '\0';
	return (istr);
}

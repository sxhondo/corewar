/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 20:17:28 by sxhondo           #+#    #+#             */
/*   Updated: 2019/05/04 13:50:41 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*istr;
	char	*estr;

	i = 0;
	estr = (char *)s;
	if (!s || !f)
		return (NULL);
	if (!(istr = ft_memalloc(ft_strlen(s) + 1)))
		return (NULL);
	while (s[i])
	{
		istr[i] = f(i, estr[i]);
		i++;
	}
	istr[i] = '\0';
	return (istr);
}

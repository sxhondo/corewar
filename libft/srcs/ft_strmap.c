/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 19:19:51 by sxhondo           #+#    #+#             */
/*   Updated: 2019/05/04 13:50:41 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strmap(char const *s, char (*f)(char))
{
	size_t	i;
	char	*istr;

	i = 0;
	if (!s || !f)
		return (NULL);
	if (!(istr = ft_memalloc(ft_strlen(s) + 1)))
		return (NULL);
	while (s[i])
	{
		istr[i] = f(s[i]);
		i++;
	}
	istr[i] = '\0';
	return (istr);
}

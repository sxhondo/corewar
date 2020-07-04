/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 22:20:36 by sxhondo           #+#    #+#             */
/*   Updated: 2019/05/04 13:50:41 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*istr;

	i = ft_strlen(s1);
	istr = (char*)malloc(sizeof(*istr) * (i + 1));
	if (!istr)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		istr[i] = s1[i];
		i++;
	}
	istr[i] = '\0';
	return (istr);
}

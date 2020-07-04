/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 19:17:41 by sxhondo           #+#    #+#             */
/*   Updated: 2019/05/26 18:41:47 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin_free(char *s1, char *s2, int w)
{
	char	*str;

	if (!s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	str = ft_strnew(ft_strlen(s1) + ft_strlen(s2));
	if (str)
	{
		ft_strcpy(str, s1);
		ft_strcat(str, s2);
	}
	if (w == 1)
		ft_strdel(&s1);
	if (w == 2)
		ft_strdel(&s2);
	return (str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 17:17:21 by sxhondo           #+#    #+#             */
/*   Updated: 2019/05/04 13:50:41 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char	*istr;
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i++;
	if (s[i] == '\0')
		return (ft_strdup(""));
	j = ft_strlen(s) - 1;
	while ((s[j] == ' ' || s[j] == '\n' || s[j] == '\t') && s[j])
		j--;
	if (!(istr = ft_memalloc(j - i + 2)))
		return (NULL);
	k = 0;
	while (k < j - i + 1)
	{
		istr[k] = s[k + i];
		k++;
	}
	istr[k] = '\0';
	return (istr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 17:59:46 by sxhondo           #+#    #+#             */
/*   Updated: 2019/07/16 17:59:48 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_realloc(void *ptr, size_t newsize)
{
	char	*str;
	char	*new;

	if (ptr && newsize == 0)
		return (NULL);
	str = (char *)ptr;
	if (!(new = ft_strnew(newsize)))
		return (NULL);
	ft_strncpy(new, str, newsize);
	return (new);
}

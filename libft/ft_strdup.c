/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylila <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 22:14:00 by ylila             #+#    #+#             */
/*   Updated: 2019/08/10 19:41:04 by mdeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char			*ft_strdup(const char *src)
{
	int		len;
	char	*new_str;

	new_str = NULL;
	len = ft_strlen(src);
	new_str = (char *)malloc(sizeof(char) * (len + 1));
	if (new_str == NULL)
		return (NULL);
	ft_strcpy(new_str, src);
	return (new_str);
}

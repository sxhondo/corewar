/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_to_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 15:00:28 by sxhondo           #+#    #+#             */
/*   Updated: 2019/09/24 15:00:29 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned				bin_to_dec(char *str)
{
	unsigned			res;
	unsigned			len;
	unsigned			i;

	i = 0;
	res = 0;
	len = ft_strlen(str);
	while (len--)
		res += ((unsigned int)str[i++] - '0') * pow_of(2, (int)len);
	return (res);
}

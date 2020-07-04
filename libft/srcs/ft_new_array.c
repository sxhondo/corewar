/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 21:09:13 by sxhondo           #+#    #+#             */
/*   Updated: 2019/12/26 13:25:21 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			*ft_new_array(int size, int c)
{
	int		i;
	int		*tab;

	if (size <= 0 || !(tab = (int *)malloc(sizeof(int *) * size)))
		return (0);
	i = -1;
	while (++i < size)
		tab[i] = c;
	return (tab);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_ptr_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 21:00:54 by sxhondo           #+#    #+#             */
/*   Updated: 2019/12/26 13:26:50 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void					**ft_new_ptr_array(int size)
{
	int					i;
	void				**tab;

	if (size <= 0 || !(tab = (void **)malloc(sizeof(void *) * size)))
		return (NULL);
	i = -1;
	while (++i < size)
		tab[i] = NULL;
	return (tab);
}

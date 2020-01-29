/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 14:51:56 by sxhondo           #+#    #+#             */
/*   Updated: 2020/01/27 14:51:57 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dasm.h"

void 			display_grid(uint8_t g[], unsigned size, int hl)
{
	for (int q = 0; q < size; q++)
	{
		if ((q % 16) == 0)
			ft_printf("\n");
		if (hl == q)
			ft_printf("{red}%02x{eoc}", g[q]);
		else
			ft_printf("%02x", g[q]);
		if (q % 2)
			ft_printf("\t");
	}
	ft_printf("\n---\n");
}

void            display_error(int num)
{
    ft_printf("error: ");
    ft_printf("%s\n", errors[num]);
    exit (num);
}
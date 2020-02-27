/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dbl_values.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylila <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 22:42:33 by ylila             #+#    #+#             */
/*   Updated: 2019/12/10 22:42:42 by ylila            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_float.h"

_Bool		get_sign(uint64_t *dbl)
{
	return (*dbl >> 63);
}

int32_t		get_exp(uint64_t *dbl)
{
	return (*dbl >> 52 & 0x7FF);
}

uint64_t	get_mantissa(uint64_t *dbl)
{
	return (*dbl & (1LL << 52) - 1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ldbl_values.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylila <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 22:08:16 by ylila             #+#    #+#             */
/*   Updated: 2019/12/10 22:08:29 by ylila            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_float.h"

_Bool		get_lsign(uint64_t *ldbl)
{
	return (*(ldbl + 1) & (1 << 15));
}

int32_t		get_lexp(uint64_t *ldbl)
{
	return (*(ldbl + 1) & 0x7FFF);
}

uint64_t	get_lmantissa(uint64_t *ldbl)
{
	return (*ldbl & 0xFFFFFFFFFFFFFFFF);
}

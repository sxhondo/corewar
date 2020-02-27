/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_log2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylila <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 22:07:56 by ylila             #+#    #+#             */
/*   Updated: 2019/12/10 22:08:00 by ylila            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_float.h"

double	ft_log2(long double num)
{
	uint64_t	*dbl;
	int32_t		exp;
	long double	pow;

	dbl = (uint64_t *)&num;
	exp = get_lexp(dbl) - 16383;
	pow = ft_pow(2, exp);
	return (exp + ((num - pow) / pow));
}

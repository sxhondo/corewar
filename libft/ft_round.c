/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_round.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylila <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 19:22:42 by ylila             #+#    #+#             */
/*   Updated: 2019/12/12 19:24:47 by ylila            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double		ft_round(double num)
{
	double	floor;
	double	ceil;

	floor = ft_floor(num);
	ceil = ft_ceil(num);
	if (num - floor == ceil - num && num > 0)
		return (ceil);
	else if (num - floor == ceil - num && num < 0)
		return (floor);
	if (num - floor < ceil - num)
		return (floor);
	return (ceil);
}

long double	ft_roundl(long double num)
{
	long double	floor;
	long double	ceil;

	floor = ft_floorl(num);
	ceil = ft_ceill(num);
	if (num - floor == ceil - num && num > 0)
		return (ceil);
	else if (num - floor == ceil - num && num < 0)
		return (floor);
	if (num - floor < ceil - num)
		return (floor);
	return (ceil);
}

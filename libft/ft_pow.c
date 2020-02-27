/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylila <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 15:01:56 by ylila             #+#    #+#             */
/*   Updated: 2019/08/10 19:41:03 by mdeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long double	ft_pow(long double num, long long power)
{
	long double	res;
	_Bool		flg;

	res = 1.;
	flg = 1;
	power < 0 ? flg = 0 : flg;
	while (power)
	{
		if (!(power % 2))
		{
			num *= num;
			power /= 2;
		}
		else
		{
			power < 0 ? ++power : --power;
			res *= num;
		}
	}
	return (!flg ? 1. / res : res);
}

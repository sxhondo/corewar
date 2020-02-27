/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylila <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 10:56:35 by ylila             #+#    #+#             */
/*   Updated: 2019/08/10 19:41:03 by mdeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	long long new;

	new = (long long)n;
	if (new < 0)
	{
		ft_putchar('-');
		new = -new;
	}
	if (new < 10)
	{
		ft_putchar(new + '0');
	}
	else
	{
		ft_putnbr(new / 10);
		ft_putnbr(new % 10);
	}
}

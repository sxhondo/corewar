/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylila <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 11:43:09 by ylila             #+#    #+#             */
/*   Updated: 2019/08/10 19:41:04 by mdeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long long new;

	new = (long long)n;
	if (new < 0)
	{
		ft_putchar_fd('-', fd);
		new = -new;
	}
	if (new < 10)
	{
		ft_putchar_fd(new + '0', fd);
	}
	else
	{
		ft_putnbr_fd(new / 10, fd);
		ft_putnbr_fd(new % 10, fd);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_converters.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 20:17:33 by sxhondo           #+#    #+#             */
/*   Updated: 2020/02/23 20:17:34 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void						write_null(t_vec *code, size_t size)
{
	union u_int32			k;

	k.num = 0;
	while (size--)
		int32_converter(code, sizeof(uint8_t), k);
}

void						int32_converter(t_vec *code, unsigned size,
			union u_int32 k)
{
	size_t					i;
	uint8_t					octets[4];

	octets[3] = k.octets.o4;
	octets[2] = k.octets.o3;
	octets[1] = k.octets.o2;
	octets[0] = k.octets.o1;
	i = size - 1;
	while (size--)
	{
		ft_vec_add(&code, &octets[i]);
		i--;
	}
}

int32_t						core_atoi(const char *str)
{
	unsigned long			result;
	size_t					i;
	int						sign;

	result = 0;
	i = 0;
	sign = (str[i] == '-') ? -1 : 1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
	{
		if ((result > INT64_MAX || (result == INT64_MAX && (str[i] - '0') > 7))
			&& sign == 1)
			return (-1);
		else if ((result > INT64_MAX
		|| (result == INT64_MAX && (str[i] - '0') > 8))
				&& sign == -1)
			return (0);
		result = result * 10 + (str[i++] - '0');
	}
	return ((int32_t)(result * sign));
}

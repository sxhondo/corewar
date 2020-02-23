/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 19:24:16 by sxhondo           #+#    #+#             */
/*   Updated: 2020/02/23 19:24:16 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dasm.h"

int32_t						set_bits(const int8_t save[], int arg_size)
{
	union u_int32			k;

	k.num = 0;
	if (arg_size == 4)
	{
		k.octets.o4 = save[0];
		k.octets.o3 = save[1];
		k.octets.o2 = save[2];
		k.octets.o1 = save[3];
	}
	if (arg_size == 3)
	{
		k.octets.o3 = save[0];
		k.octets.o2 = save[1];
		k.octets.o1 = save[2];
	}
	if (arg_size == 2)
	{
		k.octets.o2 = save[0];
		k.octets.o1 = save[1];
	}
	if (arg_size == 1)
		k.octets.o1 = save[0];
	return (k.num);
}

int32_t						get_dir_undir(const uint8_t code[], int p, int ar_s)
{
	int						i;
	int						sign;
	uint32_t				ret;
	int8_t					save[ar_s];

	i = -1;
	sign = code[p] & 0x80u ? 1 : 0;
	while (++i < ar_s)
		save[i] = sign ? ~(code[p + i]) : code[p + i];
	ret = set_bits(save, ar_s);
	return (sign ? -(ret + 1) : ret);
}

uint8_t						get_size(uint8_t arg_type_code, uint8_t op)
{
	if (arg_type_code == REG_CODE)
		return (1u);
	else if (arg_type_code == DIR_CODE)
		return (g_op_tab[op - 1].t_dir_size);
	else if (arg_type_code == IND_CODE)
		return (IND_SIZE);
	else
	{
		d_error(INVALID_ARG_SIZE);
		return (-1);
	}
}

uint8_t						get_reg(const uint8_t code[], int pos)
{
	uint8_t					ret;

	ret = code[pos];
	if (ret < 0x01 || ret > 0x10)
		d_error(REGISTER_OUT_OF_BOUNDS);
	return (ret);
}

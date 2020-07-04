/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 17:51:50 by bdudley           #+#    #+#             */
/*   Updated: 2019/11/08 19:15:48 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

short int			get_address(short int shift)
{
	shift %= MEM_SIZE;
	if (shift < 0)
		shift += MEM_SIZE;
	else if (shift > 4095)
		shift -= MEM_SIZE;
	return (shift);
}

unsigned short int	reverse_short_int(unsigned short int num)
{
	short int		rev_num;

	rev_num = 0;
	rev_num += ((num & 0xff) << (8 * 1));
	rev_num += ((num & 0xff00) >> (8 * 1));
	return (rev_num);
}

int					reverse_int(int num)
{
	int				rev_num;

	rev_num = 0;
	rev_num += ((num & 0xff) << (8 * 3));
	rev_num += ((num & 0xff00) << (8 * 1));
	rev_num += ((num & 0xff0000) >> (8 * 1));
	rev_num += ((num & 0xff000000) >> (8 * 3));
	return (rev_num);
}

int					get_bytes_to_skip(int num, unsigned char code_arg)
{
	char			copy;
	int				i;
	int				summ;

	i = -1;
	summ = 2;
	while (++i < g_op_tab[num].count_args)
	{
		copy = (code_arg >> (6 - i * 2)) & 0x3;
		if (copy == 3)
			summ += IND_SIZE;
		else if (copy == 1)
			summ += 1;
		else if (copy == 2)
			summ += g_op_tab[num].t_dir_size;
		copy = code_arg;
	}
	return (summ);
}

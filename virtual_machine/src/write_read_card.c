/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_read_card.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 19:09:46 by bdudley           #+#    #+#             */
/*   Updated: 2020/02/09 14:39:37 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		read_card(void *dst, void *src, short int value, int length)
{
	short int	size;

	size = ((MEM_SIZE - value) > length) ? length : MEM_SIZE - value;
	if (size > 0)
		ft_memcpy(dst, src + value, size);
	if (size < length)
		ft_memcpy(dst + size, src, length - size);
}

void		write_card(void *dst, void *src, short int value, int length)
{
	short int	size;

	size = ((MEM_SIZE - value) > length) ? length : MEM_SIZE - value;
	if (size > 0)
		ft_memcpy(dst + value, src, size);
	if (size < length)
		ft_memcpy(dst, src + size, length - size);
}

void		usage(void)
{
	ft_putstr("usage: ./corewar [-dump [<cycle> |\
-666]] [[-n] champion.cor ...]\n");
	ft_putstr("\t[-dump -666] runs epic war in visual mode\n");
	ft_putstr("\tmaximum number of players is defined by MAX_PLAYERS macro\n");
	ft_putstr("\tuse champions created by ./asm\n");
	ft_putstr("\tto assign number to a champion use [-n] before dedicated \
champion, otherwise number left will be used\n");
	exit(1);
}

void		save_carry(t_processes **prs,
		unsigned char *arena, unsigned char arg_reg)
{
	short int shift;

	shift = (*prs)->carry;
	set_t_reg((*prs)->reg[arg_reg], 3, arena, prs);
	(*prs)->carry = shift;
}

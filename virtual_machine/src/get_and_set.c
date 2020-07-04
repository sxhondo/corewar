/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_and_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 17:51:50 by bdudley           #+#    #+#             */
/*   Updated: 2020/02/01 21:23:36 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int					get_arg(unsigned char code_arg, short int *shift,
		unsigned char *arena, t_processes **prs)
{
	short int		current_location;
	int				value;

	value = 0;
	current_location = (*prs)->index;
	if (code_arg == REG_CODE)
		*shift += get_t_reg(&value, *shift, arena, prs);
	else if (code_arg == DIR_CODE)
	{
		if (g_op_tab[(*prs)->code_op - 1].t_dir_size == 2)
			value = get_t_ind(current_location, *shift, arena, 0);
		else
		{
			value = get_t_dir(current_location, *shift, arena);
			*shift += 2;
		}
		*shift += 2;
	}
	else if (code_arg == IND_CODE)
	{
		value = get_t_ind(current_location, *shift, arena, 1);
		value = get_t_dir(current_location, value, arena);
		*shift += IND_SIZE;
	}
	return (value);
}

short int			get_t_ind(short int current_location,
		int shift, unsigned char *arena, int mod)
{
	short int		value;

	current_location = get_address((current_location + shift) % MEM_SIZE);
	read_card(&value, arena, current_location, IND_SIZE);
	value = reverse_short_int(value);
	if (mod)
		value %= IDX_MOD;
	return (value);
}

int					get_t_dir(short int current_location, int shift,
		unsigned char *arena)
{
	int				value;

	current_location = get_address(current_location + shift);
	read_card(&value, arena, current_location, REG_SIZE);
	value = reverse_int(value);
	return (value);
}

void				set_t_reg(int value, int shift,
		unsigned char *arena, t_processes **prs)
{
	unsigned char	arg_reg;

	arg_reg = *(arena + ((*prs)->index + shift) % MEM_SIZE) - 1;
	if (arg_reg >= 0 && arg_reg < REG_NUMBER)
	{
		(*prs)->reg[arg_reg] = value;
		(*prs)->carry = (value == 0) ? 1 : 0;
	}
}

int					get_t_reg(int *value, int shift,
		unsigned char *arena, t_processes **prs)
{
	unsigned char	arg_reg;

	arg_reg = *(arena + ((*prs)->index + shift) % MEM_SIZE) - 1;
	if (arg_reg >= 0 && arg_reg < REG_NUMBER)
	{
		*value = (*prs)->reg[arg_reg];
		return (1);
	}
	return (0);
}

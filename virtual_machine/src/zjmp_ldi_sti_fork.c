/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp_ldi_sti_fork.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 18:08:19 by bdudley           #+#    #+#             */
/*   Updated: 2020/02/01 17:40:52 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void				zjmp_op(t_info *info, t_processes **prs, t_sdl *sdl)
{
	short int		current_location;
	short int		new_location;
	short int		shift;

	current_location = (*prs)->index;
	shift = 3;
	if ((*prs)->carry)
	{
		shift = get_t_ind(current_location, 1, info->arena, 1);
	}
	new_location = get_address(shift + current_location);
	(*prs)->index = new_location;
	if (sdl != NULL)
	{
		update_byte(current_location, sdl);
		create_cursor(new_location, -(*prs)->reg[0] - 1, sdl);
	}
}

void				ldi_op(t_info *info, t_processes **prs, t_sdl *sdl)
{
	unsigned char	code_arg;
	unsigned char	arg_reg;
	short int		current_location;
	short int		shift;
	int				value;

	shift = 2;
	current_location = (*prs)->index;
	code_arg = ((info->arena)[(current_location + 1) % MEM_SIZE]) & 0xfc;
	value = get_arg((code_arg >> 6) & 0x3, &shift, info->arena, prs);
	if ((shift - 2) && (code_arg == 84 || code_arg == 212 || code_arg == 148 ||
				code_arg == 100 || code_arg == 228 || code_arg == 164))
	{
		value += get_arg((code_arg >> 4) & 0x3, &shift, info->arena, prs);
		if (shift + 1 == get_bytes_to_skip(9, code_arg))
			if ((arg_reg = *((info->arena) + (current_location + shift) %
					MEM_SIZE) - 1) >= 0 && arg_reg < REG_NUMBER)
			{
				value = get_address(current_location + value % IDX_MOD);
				read_card((*prs)->reg + arg_reg, info->arena, value, REG_SIZE);
				(*prs)->reg[arg_reg] = reverse_int((*prs)->reg[arg_reg]);
			}
	}
	shift_next_op(code_arg, 9, prs, sdl);
}

void				sti_op(t_info *info, t_processes **prs, t_sdl *sdl)
{
	unsigned char	code_arg;
	unsigned char	arg_reg;
	short int		shift;
	int				value;

	shift = 3;
	code_arg = ((info->arena)[((*prs)->index + 1) % MEM_SIZE]) & 0xfc;
	value = get_arg((code_arg >> 4) & 0x3, &shift, info->arena, prs);
	if ((shift - 3) && (code_arg == 84 || code_arg == 88 || code_arg == 120 ||
						code_arg == 100 || code_arg == 104 || code_arg == 116))
	{
		value += get_arg((code_arg >> 2) & 0x3, &shift, info->arena, prs);
		if (shift == get_bytes_to_skip(10, code_arg) && (arg_reg =
		*((info->arena) + ((*prs)->index + 2) % MEM_SIZE) - 1)
		>= 0 && arg_reg < REG_NUMBER)
		{
			shift = get_address((*prs)->index + value % IDX_MOD);
			value = reverse_int((*prs)->reg[arg_reg]);
			write_card(info->arena, &value, shift, REG_SIZE);
			if (sdl != NULL)
				update_bytes(shift, 8, -(*prs)->reg[0] - 1, sdl);
		}
	}
	shift_next_op(code_arg, 10, prs, sdl);
}

void				fork_op(t_info *info, t_processes **prs, t_sdl *sdl)
{
	short int		current_location;
	short int		new_location;
	short int		num_player;
	short int		arg;
	int				i;

	current_location = (*prs)->index;
	num_player = ((*prs)->reg)[0];
	arg = get_t_ind(current_location, 1, info->arena, 1);
	add_elem(&(info->processes), arg, -num_player - 1);
	info->processes->carry = (*prs)->carry;
	(info->processes)->cc_live = (*prs)->cc_live;
	new_location = get_address(current_location + arg);
	i = -1;
	while (++i < REG_NUMBER)
		(info->processes)->reg[i] = (*prs)->reg[i];
	if (sdl != NULL)
	{
		move_cursor(current_location, 1 + IND_SIZE, -num_player - 1, sdl);
		create_cursor(new_location, -num_player - 1, sdl);
		Mix_PlayChannel(-1, sdl->birth_effect, 0);
	}
	(*prs)->index = get_address((current_location + 1 + IND_SIZE));
	info->processes->index = new_location;
	++info->count_process;
}

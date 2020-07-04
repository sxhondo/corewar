/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live_ld_st_add.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 18:05:20 by bdudley           #+#    #+#             */
/*   Updated: 2020/02/08 13:44:17 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void				live_op(t_info *info, t_processes **prs, t_sdl *sdl)
{
	int				number_player;
	int				arg_player;
	short int		new_location;
	short int		current_location;

	current_location = (*prs)->index;
	number_player = (*prs)->reg[0];
	(*prs)->cc_live = info->count_cycles;
	arg_player = get_t_dir(current_location, 1, info->arena);
	if (-arg_player - 1 >= 0 && -arg_player - 1 < MAX_PLAYERS
	&& info->players[-arg_player - 1].magic == COREWAR_EXEC_MAGIC)
	{
		info->last_live = -arg_player;
		if (sdl != NULL)
			update_live(-arg_player - 1, info->count_cycles, sdl);
	}
	new_location = (current_location + 1 + DIR_SIZE) % MEM_SIZE;
	if (sdl != NULL)
	{
		move_cursor(current_location, 1 + DIR_SIZE,
				-number_player - 1, sdl);
		Mix_PlayChannel(-1, sdl->live_effect, 0);
	}
	(*prs)->index = new_location;
	++info->count_live;
}

void				ld_op(t_info *info, t_processes **prs, t_sdl *sdl)
{
	unsigned char	code_arg;
	short int		current_location;
	short int		shift;
	int				value;

	current_location = (*prs)->index;
	shift = 2;
	code_arg = ((info->arena)[((*prs)->index + 1) % MEM_SIZE]) & 0xf0;
	if (code_arg == 208)
	{
		shift = get_t_ind(current_location, shift, info->arena, 1);
		value = get_t_dir(current_location, shift, info->arena);
		set_t_reg(value, 2 + IND_SIZE, info->arena, prs);
	}
	else if (code_arg == 144)
	{
		value = get_t_dir(current_location, shift, info->arena);
		set_t_reg(value, 2 + DIR_SIZE, info->arena, prs);
	}
	shift_next_op(code_arg, 1, prs, sdl);
}

void				st_op(t_info *info, t_processes **prs, t_sdl *sdl)
{
	unsigned char	code_arg;
	unsigned char	arg_reg;
	short int		shift;
	short int		current_location;
	int				value;

	current_location = (*prs)->index;
	if ((code_arg = ((info->arena)[(current_location + 1)
				% MEM_SIZE]) & 0xf0) == 112 || code_arg == 80)
		if ((arg_reg = *((info->arena) + (current_location + 2)
				% MEM_SIZE) - 1) >= 0 && arg_reg < REG_NUMBER)
		{
			if (code_arg == 80)
				save_carry(prs, info->arena, arg_reg);
			else
			{
				shift = get_address(get_t_ind(current_location + 3,
						0, info->arena, 1) + current_location);
				value = reverse_int((*prs)->reg[arg_reg]);
				write_card(info->arena, &value, shift, REG_SIZE);
				if (sdl != NULL)
					update_bytes(shift, REG_SIZE, -(*prs)->reg[0] - 1, sdl);
			}
		}
	shift_next_op(code_arg, 2, prs, sdl);
}

void				add_op(t_info *info, t_processes **prs, t_sdl *sdl)
{
	unsigned char	code_arg;
	unsigned char	arg_reg;
	unsigned char	arg_reg2;
	short int		current_location;

	current_location = (*prs)->index;
	code_arg = ((info->arena)[(current_location + 1) % MEM_SIZE]) & 0xfc;
	if (code_arg == 84)
	{
		arg_reg = *((info->arena) + (current_location + 2) % MEM_SIZE) - 1;
		arg_reg2 = *((info->arena) + (current_location + 3)
				% MEM_SIZE) - 1;
		if (arg_reg2 >= 0 && arg_reg2 < REG_NUMBER &&
		arg_reg >= 0 && arg_reg < REG_NUMBER)
			set_t_reg((*prs)->reg[arg_reg] + (*prs)->reg[arg_reg2],
					4, info->arena, prs);
	}
	shift_next_op(code_arg, 3, prs, sdl);
}

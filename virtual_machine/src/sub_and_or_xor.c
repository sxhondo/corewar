/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_and_or_xor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 18:07:09 by bdudley           #+#    #+#             */
/*   Updated: 2019/11/15 18:07:09 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void				sub_op(t_info *info, t_processes **prs, t_sdl *sdl)
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
			set_t_reg((*prs)->reg[arg_reg] - (*prs)->reg[arg_reg2],
					4, info->arena, prs);
	}
	shift_next_op(code_arg, 4, prs, sdl);
}

void				and_op(t_info *info, t_processes **prs, t_sdl *sdl)
{
	unsigned char	code_arg;
	short int		current_location;
	short int		shift;
	int				value;

	shift = 2;
	current_location = (*prs)->index;
	code_arg = ((info->arena)[(current_location + 1) % MEM_SIZE]) & 0xfc;
	value = get_arg((code_arg >> 6) & 0x3, &shift, info->arena, prs);
	if (shift - 2)
		value &= get_arg((code_arg >> 4) & 0x3, &shift, info->arena, prs);
	{
		if (shift + 1 == get_bytes_to_skip(5, code_arg))
			set_t_reg(value, shift, info->arena, prs);
	}
	shift_next_op(code_arg, 5, prs, sdl);
}

void				or_op(t_info *info, t_processes **prs, t_sdl *sdl)
{
	unsigned char	code_arg;
	short int		current_location;
	short int		shift;
	int				value;

	shift = 2;
	current_location = (*prs)->index;
	code_arg = ((info->arena)[(current_location + 1) % MEM_SIZE]) & 0xfc;
	value = get_arg((code_arg >> 6) & 0x3, &shift, info->arena, prs);
	if ((shift - 2))
		value |= get_arg((code_arg >> 4) & 0x3, &shift, info->arena, prs);
	{
		if (shift + 1 == get_bytes_to_skip(6, code_arg))
			set_t_reg(value, shift, info->arena, prs);
	}
	shift_next_op(code_arg, 6, prs, sdl);
}

void				xor_op(t_info *info, t_processes **prs, t_sdl *sdl)
{
	unsigned char	code_arg;
	short int		current_location;
	short int		shift;
	int				value;

	shift = 2;
	current_location = (*prs)->index;
	code_arg = ((info->arena)[(current_location + 1) % MEM_SIZE]) & 0xfc;
	value = get_arg((code_arg >> 6) & 0x3, &shift, info->arena, prs);
	if ((shift - 2))
		value ^= get_arg((code_arg >> 4) & 0x3, &shift, info->arena, prs);
	{
		if (shift + 1 == get_bytes_to_skip(7, code_arg))
			set_t_reg(value, shift, info->arena, prs);
	}
	shift_next_op(code_arg, 7, prs, sdl);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lld_lldi_lfork_aff.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 18:10:13 by bdudley           #+#    #+#             */
/*   Updated: 2020/02/08 13:57:47 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void				lld_op(t_info *info, t_processes **prs, t_sdl *sdl)
{
	unsigned char	code_arg;
	short int		current_location;
	short int		shift;
	int				value;

	shift = 2;
	current_location = (*prs)->index;
	code_arg = ((info->arena)[(current_location + 1) % MEM_SIZE]) & 0xf0;
	if (code_arg == 208 || code_arg == 144)
	{
		if (code_arg == 208)
		{
			shift = get_t_ind(current_location, shift, info->arena, 0);
			value = get_t_ind(current_location, shift, info->arena, 0);
		}
		else
			value = get_t_dir(current_location, shift, info->arena);
		shift = (code_arg == 208) ? 2 + IND_SIZE : 2 + DIR_SIZE;
		set_t_reg(value, shift, info->arena, prs);
	}
	shift_next_op(code_arg, 12, prs, sdl);
}

void				lldi_op(t_info *info, t_processes **prs, t_sdl *sdl)
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
		value += get_arg((code_arg >> 4) & 0x3, &shift, info->arena, prs);
	if (shift + 1 == get_bytes_to_skip(9, code_arg))
	{
		if ((arg_reg = *((info->arena) + (current_location + shift) % MEM_SIZE)
				- 1) >= 0 && arg_reg < REG_NUMBER)
		{
			value = get_address(current_location + value);
			read_card((*prs)->reg + arg_reg, info->arena, value, REG_SIZE);
			(*prs)->reg[arg_reg] = reverse_int((*prs)->reg[arg_reg]);
			(*prs)->carry = ((*prs)->reg[arg_reg] == 0) ? 1 : 0;
		}
	}
	shift_next_op(code_arg, 13, prs, sdl);
}

void				lfork_op(t_info *info, t_processes **prs, t_sdl *sdl)
{
	short int		current_location;
	short int		num_player;
	short int		arg;
	int				i;

	current_location = (*prs)->index;
	num_player = ((*prs)->reg)[0];
	arg = get_address(current_location +
			get_t_ind(current_location, 1, info->arena, 0));
	add_elem(&(info->processes), arg, num_player);
	info->processes->carry = (*prs)->carry;
	(info->processes)->cc_live = (*prs)->cc_live;
	i = -1;
	while (++i < REG_NUMBER)
		(info->processes)->reg[i] = (*prs)->reg[i];
	if (sdl != NULL)
	{
		move_cursor(current_location, 1 + IND_SIZE, -num_player - 1, sdl);
		create_cursor(current_location + arg, -num_player - 1, sdl);
		Mix_PlayChannel(-1, sdl->birth_effect, 0);
	}
	(*prs)->index = get_address((current_location + 1 + IND_SIZE));
	info->processes->index = arg;
	++info->count_process;
}

void				aff_op(t_info *info, t_processes **prs, t_sdl *sdl)
{
	unsigned char	code_arg;
	short int		arg_reg;
	char			announcement[9];
	char			sumbol;

	ft_bzero(announcement, 9);
	code_arg = ((info->arena)[((*prs)->index + 1) % MEM_SIZE]) & 0xc0;
	if (code_arg == 64)
	{
		arg_reg = *((info->arena) + ((*prs)->index + 2) % MEM_SIZE) - 1;
		if (arg_reg >= 0 && arg_reg < REG_NUMBER)
		{
			sumbol = (*prs)->reg[arg_reg];
			ft_strcpy(announcement, "Aff: ");
			announcement[5] = sumbol;
			ft_strcat(announcement, "\n");
			ft_putstr(announcement);
		}
	}
	shift_next_op(code_arg, 15, prs, sdl);
}

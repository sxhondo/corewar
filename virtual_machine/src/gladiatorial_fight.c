/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gladiatorial_fight.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 17:20:05 by bdudley           #+#    #+#             */
/*   Updated: 2020/02/08 13:48:18 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "visual.h"
#include <stdio.h>

void		take_actions(t_info *info, t_processes *prs, t_sdl *sdl)
{
	if (prs->cc_op == 0)
	{
		prs->code_op = info->arena[prs->index];
		if ((info->arena)[prs->index] > 0 &&
		(info->arena)[prs->index] <= COUNT_OP)
			prs->cc_op = g_op_tab[prs->code_op - 1].cycle_for_exec;
	}
	if (prs->cc_op > 0)
		--prs->cc_op;
	if (prs->cc_op == 0)
	{
		if (prs->code_op > 0 && prs->code_op <= COUNT_OP)
		{
			g_op_tab[prs->code_op - 1].func(info, &prs, sdl);
		}
		else
		{
			if (sdl != NULL)
				move_cursor(prs->index, 1, -prs->reg[0] - 1, sdl);
			prs->index = (++(prs->index)) % MEM_SIZE;
		}
	}
}

void		kick_noobs(t_info *info, t_sdl *sdl)
{
	t_processes		*ptr;

	ptr = info->processes;
	while (ptr)
		if (info->count_cycles - ptr->cc_live >= info->cycle_to_die)
		{
			if (sdl != NULL)
			{
				update_byte(ptr->index, sdl);
				add_explosion(create_explosion(ptr->index),
										&sdl->head_explosion);
			}
			delete_elem(&ptr, info);
			--info->count_process;
		}
		else
			ptr = ptr->next;
	++(info->count_check);
	if (info->count_live >= NBR_LIVE || info->count_check == MAX_CHECKS)
	{
		info->count_check = 0;
		info->cycle_to_die -= CYCLE_DELTA;
	}
	info->i = 0;
	info->count_live = 0;
}

void		gladiatorial_fight(int *play, t_info *info, t_sdl *sdl)
{
	t_processes	*prs;

	if (info->processes)
	{
		++info->i;
		prs = info->processes;
		++info->count_cycles;
		while (prs)
		{
			take_actions(info, prs, sdl);
			prs = prs->next;
		}
		if (info->i >= info->cycle_to_die)
			kick_noobs(info, sdl);
		return ;
	}
	else
		*play = -1;
}

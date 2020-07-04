/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_replica.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 15:44:28 by rgyles            #+#    #+#             */
/*   Updated: 2020/01/19 15:45:46 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"
#include "corewar.h"

/*
** set duplicating array to represent which codes belongs to which player
*/

void	set_replica(t_processes *processes, t_info *info, t_sdl *sdl)
{
	int				i;
	int				end;
	int				player;
	unsigned char	*replica;

	player = 1;
	replica = sdl->replica;
	while (processes != NULL)
	{
		i = processes->index;
		end = i + ((info->players)[player - 1]).prog_size;
		while (i < end)
			replica[i++] = player;
		++player;
		processes = processes->prev;
	}
}

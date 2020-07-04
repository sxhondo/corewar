/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_byte_c.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 15:46:42 by rgyles            #+#    #+#             */
/*   Updated: 2020/02/01 16:45:11 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"
#include "op.h"

/*
** закрепить байт под индексом за определенным игроком
*/

void	set_byte(int location, int player, t_sdl *sdl)
{
	sdl->replica[location] = player + 1;
}

void	update_byte(int location, t_sdl *sdl)
{
	set_nibble_for_render(location, CODE, sdl->replica[location], sdl);
	draw_byte(sdl->arena[location], sdl->render_info, sdl->surface);
}

void	update_bytes(int location, int length, int player, t_sdl *sdl)
{
	int i;
	int	index;

	i = 0;
	while (i < length)
	{
		index = location + i++;
		if (index >= MEM_SIZE)
			index = index % MEM_SIZE;
		set_byte(index, player, sdl);
	}
	i = 0;
	while (i < length)
	{
		index = location + i++;
		if (index >= MEM_SIZE)
			index = index % MEM_SIZE;
		update_byte(index, sdl);
	}
}

/*
** player comes from processes info.
** where player number start from 0
*/

void	create_cursor(int location, int player, t_sdl *sdl)
{
	set_nibble_for_render(location, CURSOR, player + 1, sdl);
	draw_byte(sdl->arena[location], sdl->render_info, sdl->surface);
}

/*
** location - индекс где курсор сейчас
** shift - сдвиг
*/

void	move_cursor(int location, int shift, int player, t_sdl *sdl)
{
	create_cursor((location + shift) % MEM_SIZE, player, sdl);
	update_byte(location, sdl);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 20:00:07 by rgyles            #+#    #+#             */
/*   Updated: 2020/01/25 13:54:22 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl_struct.h"
#include "op.h"
#include "visual.h"

void	fill_in_vertial(int value, int index,
			int length, unsigned char *replica)
{
	int i;

	i = -1;
	while (++i < length)
		replica[index + i * 64] = value;
}

void	fill_in_horizontal(int value, int index,
				int length, unsigned char *replica)
{
	int i;

	i = -1;
	while (++i < length)
		replica[index++] = value;
}

/*
** length - side of square
** shift - square side plus 1
** while is till median
*/

void	form_squares(int seed, t_sdl *sdl)
{
	int start;
	int shift;
	int	length;

	start = 0;
	length = 64;
	shift = 65;
	while (start < MEM_SIZE / 2)
	{
		fill_in_vertial(seed % 5, start, length, sdl->replica);
		fill_in_vertial(seed % 5, start + length - 1, length, sdl->replica);
		fill_in_horizontal(seed % 5, start, length, sdl->replica);
		fill_in_horizontal(seed % 5, start + (length - 1) * 64,
											length, sdl->replica);
		++seed;
		start += shift;
		length -= 2;
	}
}

void	epilepsy(int seed, t_render *render_info,
							SDL_Surface *surface, t_sdl *sdl)
{
	int			i;
	int			end_of_row;
	int			row;

	form_squares(seed, sdl);
	i = 0;
	set_nibble_for_render(i, EMPTY, 0, sdl);
	row = i / 64;
	end_of_row = (row + 1) * 64;
	while (i < MEM_SIZE)
	{
		while (i < end_of_row)
		{
			render_info->font_color = sdl->colors[sdl->replica[i] + FONT_COLOR];
			draw_byte(sdl->arena[i++], render_info, surface);
			render_info->rect.x += NIBBLE_WIDTH;
		}
		render_info->rect.y += NIBBLE_HEIGHT;
		render_info->rect.x = NIBBLE_X_SHIFT;
		end_of_row = (++row + 1) * 64;
		i = end_of_row - 64;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_byte.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 15:05:41 by rgyles            #+#    #+#             */
/*   Updated: 2020/02/09 14:24:47 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"

/*
** nibble is 4 bits!
*/

char	get_nibble(unsigned char nibble)
{
	if (nibble < 10)
		return (48 + nibble);
	else if (nibble == 10)
		return ('a');
	else if (nibble == 11)
		return ('b');
	else if (nibble == 12)
		return ('c');
	else if (nibble == 13)
		return ('d');
	else if (nibble == 14)
		return ('e');
	else
		return ('f');
}

/*
** set color and location for nibble
*/

void	set_nibble_for_render(int location, int type, int player, t_sdl *sdl)
{
	if (type == EMPTY)
	{
		sdl->render_info->font_color = sdl->colors[WHITE];
		sdl->render_info->back_color = sdl->colors[BLACK];
	}
	else if (type == CURSOR)
	{
		sdl->render_info->font_color = sdl->colors[WHITE];
		if (player < 1 || player > 4)
			sdl->render_info->back_color = sdl->colors[GREY];
		else
			sdl->render_info->back_color = sdl->colors[player + BACK_COLOR];
	}
	else
	{
		if (player < 1 || player > 4)
			sdl->render_info->font_color = sdl->colors[WHITE];
		else
			sdl->render_info->font_color = sdl->colors[player + FONT_COLOR];
		sdl->render_info->back_color = sdl->colors[BLACK];
	}
	sdl->render_info->rect.x = NIBBLE_X_SHIFT + NIBBLE_WIDTH * (location % 64);
	sdl->render_info->rect.y = NIBBLE_Y_SHIFT + NIBBLE_HEIGHT * (location / 64);
}

/*
** render single byte:
** divide byte into nibbles,
** get the corresponding base 16 symbols,
** form a string; then
** render text using TTF, set coordinates,
** copy to window surface, free orginal surface created by TTF
*/

void	draw_byte(unsigned char byte, t_render *render_info,
										SDL_Surface *surface)
{
	char		cell[3];
	SDL_Surface	*text_surface;

	cell[0] = get_nibble((byte & 0xf0) >> 4);
	cell[1] = get_nibble(byte & 0xf);
	cell[2] = '\0';
	text_surface = TTF_RenderText_Shaded(render_info->font, cell,
					render_info->font_color, render_info->back_color);
	SDL_BlitSurface(text_surface, NULL, surface, &render_info->rect);
	SDL_FreeSurface(text_surface);
}

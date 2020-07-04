/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_text.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 20:02:31 by rgyles            #+#    #+#             */
/*   Updated: 2020/01/25 12:22:03 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"

void	render_text(char *text, t_render *render_info, SDL_Surface *surface)
{
	SDL_Surface	*text_surface;

	text_surface = TTF_RenderText_Shaded(render_info->font, text,
					render_info->font_color, render_info->back_color);
	SDL_BlitSurface(text_surface, NULL, surface, &render_info->rect);
	SDL_FreeSurface(text_surface);
}

void	render_text_outline(char *text,
			t_render *render_info, t_sdl *sdl)
{
	SDL_Surface	*bg;
	SDL_Surface	*fg;
	SDL_Rect	rect;

	rect = (SDL_Rect) {OUTLINE, OUTLINE, 0, 0};
	bg = TTF_RenderText_Blended(sdl->outline_font, text,
									render_info->back_color);
	fg = TTF_RenderText_Blended(render_info->font, text,
									render_info->font_color);
	SDL_BlitSurface(fg, NULL, bg, &rect);
	SDL_FreeSurface(fg);
	SDL_BlitSurface(bg, NULL, sdl->surface, &render_info->rect);
	SDL_FreeSurface(bg);
}

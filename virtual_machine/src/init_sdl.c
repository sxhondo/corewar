/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 14:45:48 by rgyles            #+#    #+#             */
/*   Updated: 2020/02/01 17:04:30 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"
#include "sound.h"
#include "op.h"
#include "libft.h"

static void	init_colors(SDL_Color *colors)
{
	colors[BLACK] = (SDL_Color) {0, 0, 0, 0};
	colors[WHITE] = (SDL_Color) {255, 255, 255, 0};
	colors[YELLOW] = (SDL_Color) {255, 255, 0, 0};
	colors[BLUE] = (SDL_Color) {0, 150, 255, 0};
	colors[GREEN] = (SDL_Color) {0, 255, 0, 0};
	colors[RED] = (SDL_Color) {255, 0, 0, 0};
	colors[YELLOW_BACK] = (SDL_Color) {255, 150, 0, 0};
	colors[BLUE_BACK] = (SDL_Color) {0, 150, 255, 0};
	colors[GREEN_BACK] = (SDL_Color) {0, 150, 0, 0};
	colors[RED_BACK] = (SDL_Color) {150, 0, 0, 0};
	colors[GREY] = (SDL_Color) {64, 64, 64, 0};
}

static void	init_font(TTF_Font **outline_font, t_render *render_info)
{
	TTF_Font *font;

	if (TTF_Init() == -1)
		exit(error_message("TTF_Init", TTF_GetError()));
	render_info->font = TTF_OpenFont(FONT_PATH, FONT_SIZE);
	if (render_info->font == NULL)
		exit(error_message("TTF_OpenFont", TTF_GetError()));
	font = TTF_OpenFont(FONT_PATH, FONT_SIZE_ANNOUNCE);
	if (font == NULL)
		exit(error_message("TTF_OpenFont", TTF_GetError()));
	TTF_SetFontStyle(render_info->font, TTF_STYLE_BOLD);
	TTF_SetFontStyle(font, TTF_STYLE_BOLD);
	TTF_SetFontOutline(font, OUTLINE);
	*outline_font = font;
}

void		init_music(t_sdl *sdl)
{
	int flags;

	flags = MIX_INIT_MP3;
	if (flags != Mix_Init(flags))
		exit(error_message("Mix_Init", Mix_GetError()));
	if (Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640) == -1)
		exit(error_message("Mix_OpenAudio", Mix_GetError()));
	if ((sdl->main_theme = Mix_LoadMUS(MAIN_THEME)) == NULL)
		exit(error_message("Mix_LoadMUS", Mix_GetError()));
	Mix_VolumeMusic(50);
	if ((sdl->live_effect = Mix_LoadWAV(LIVE_EFFECT)) == NULL)
		exit(error_message("MixLoadWAV", Mix_GetError()));
	if ((sdl->birth_effect = Mix_LoadWAV(BIRTH_EFFECT)) == NULL)
		exit(error_message("MixLoadWAV", Mix_GetError()));
	Mix_VolumeChunk(sdl->live_effect, MIX_MAX_VOLUME);
	Mix_VolumeChunk(sdl->birth_effect, MIX_MAX_VOLUME);
}

int			init_sdl(unsigned char *arena, t_sdl *sdl)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
		exit(error_message("SDL_Init", SDL_GetError()));
	sdl->window = SDL_CreateWindow("Corewar", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	if (sdl->window == NULL)
		exit(error_message("SDL_CreateWindow", SDL_GetError()));
	sdl->surface = SDL_GetWindowSurface(sdl->window);
	if (sdl->surface == NULL)
		exit(error_message("SDL_GetWindowSurface", SDL_GetError()));
	sdl->head_explosion = NULL;
	SDL_FreeSurface(sdl->surface);
	sdl->render_info = (t_render *)malloc(sizeof(t_render));
	if (sdl->render_info == NULL)
		exit(error_message("malloc", "sdl->render_info"));
	init_font(&sdl->outline_font, sdl->render_info);
	sdl->img_data = (int *)sdl->surface->pixels;
	if ((sdl->replica = malloc(MEM_SIZE)) == NULL)
		exit(error_message("malloc", "sdl->replica"));
	ft_bzero(sdl->replica, MEM_SIZE);
	init_music(sdl);
	init_colors(sdl->colors);
	sdl->arena = arena;
	return (0);
}

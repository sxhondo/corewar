/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resources.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 14:49:35 by rgyles            #+#    #+#             */
/*   Updated: 2020/01/12 15:23:47 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl_struct.h"

/*
** from top to bottom:
** free sound effect
** close mixer
** free music
** clear all library handles create by Mix_Init
*/

void	free_music(t_sdl *sdl)
{
	Mix_FreeChunk(sdl->live_effect);
	Mix_CloseAudio();
	Mix_FreeMusic(sdl->main_theme);
	Mix_Quit();
}

void	free_ttf(t_sdl *sdl)
{
	TTF_CloseFont(sdl->render_info->font);
	TTF_CloseFont(sdl->outline_font);
	TTF_Quit();
}

void	free_resources(t_sdl *sdl)
{
	free_music(sdl);
	free_ttf(sdl);
	free(sdl->render_info);
	SDL_DestroyWindow(sdl->window);
	SDL_Quit();
}

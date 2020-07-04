/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 17:49:29 by rgyles            #+#    #+#             */
/*   Updated: 2020/02/09 16:14:47 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"
#include "corewar.h"

/*
** no need to update surface if game is running
*/

void	update_game_status(int status, t_sdl *sdl)
{
	t_render *render_info;

	render_info = sdl->render_info;
	render_info->rect.x = GAME_STATUS_X_LOCATION;
	render_info->rect.y = GAME_STATUS_Y_LOCATION;
	if (status == 1)
	{
		render_info->font_color = sdl->colors[GREEN];
		render_text("RUNNING", render_info, sdl->surface);
	}
	else
	{
		render_info->rect.w = GAME_STATUS_WIDTH;
		render_info->font_color = sdl->colors[RED];
		SDL_FillRect(sdl->surface, &render_info->rect, 0);
		render_text("PAUSED", render_info, sdl->surface);
		SDL_UpdateWindowSurface(sdl->window);
	}
}

void	update_value(int data, t_render *render_info, SDL_Surface *surface)
{
	char	buffer[30];

	int_to_char(data, buffer);
	render_text(buffer, render_info, surface);
}

void	udpate_delay(int delay, t_sdl *sdl)
{
	t_render *render_info;

	render_info = sdl->render_info;
	render_info->rect.x = SDL_DATA_X_LOCATION;
	render_info->rect.y = SDL_DATA_Y_LOCATION;
	render_info->rect.w = SDL_DATA_WIDTH;
	render_info->font_color = sdl->colors[WHITE];
	render_info->back_color = sdl->colors[BLACK];
	SDL_FillRect(sdl->surface, &sdl->render_info->rect, 0);
	if (delay == 0)
		render_text("no delay", render_info, sdl->surface);
	else
		update_value(delay, render_info, sdl->surface);
}

void	update_live(int player, int value, t_sdl *sdl)
{
	t_render render_info;

	(void)value;
	render_info.font_color = sdl->colors[WHITE];
	render_info.back_color = sdl->colors[BLACK];
	render_info.font = sdl->render_info->font;
	render_info.rect.x = LIVE_X_LOCATION;
	render_info.rect.y = PLAYER_Y_LOCATION +
			PLAYER_SECTION_HEIGHT * player + 40;
	render_info.rect.w = SDL_DATA_WIDTH;
	render_info.rect.h = NIBBLE_HEIGHT;
	SDL_FillRect(sdl->surface, &(render_info.rect), 0);
	update_value(value, &render_info, sdl->surface);
}

void	show_data(t_info *info, t_sdl *sdl)
{
	t_render *render_info;

	render_info = sdl->render_info;
	render_info->rect.x = DATA_X_LOCATION;
	render_info->rect.y = DATA_Y_LOCATION;
	render_info->rect.w = 150;
	render_info->rect.h = 95;
	render_info->font_color = sdl->colors[WHITE];
	render_info->back_color = sdl->colors[BLACK];
	SDL_FillRect(sdl->surface, &sdl->render_info->rect, 0);
	update_value(info->count_cycles, render_info, sdl->surface);
	sdl->render_info->rect.y += TEXT_Y_SHIFT;
	update_value(info->last_live, render_info, sdl->surface);
	sdl->render_info->rect.y += TEXT_Y_SHIFT;
	update_value(info->cycle_to_die, render_info, sdl->surface);
	sdl->render_info->rect.y += TEXT_Y_SHIFT;
	update_value(info->count_process, render_info, sdl->surface);
	sdl->render_info->rect.y += TEXT_Y_SHIFT;
	update_value(info->count_check, render_info, sdl->surface);
}

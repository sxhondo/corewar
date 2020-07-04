/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_game_controls.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 18:18:09 by rgyles            #+#    #+#             */
/*   Updated: 2020/02/01 17:05:49 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"

void	draw_game_controls(t_sdl *sdl)
{
	sdl->render_info->font_color = sdl->colors[WHITE];
	sdl->render_info->back_color = sdl->colors[BLACK];
	sdl->render_info->rect.x = INFO_X_LOCATION;
	sdl->render_info->rect.y = CONTROLS_Y_LOCATION;
	render_text("GAME CONTROLS", sdl->render_info, sdl->surface);
	sdl->render_info->rect.y += TEXT_Y_SHIFT * 2;
	render_text("run / pause - SPACE", sdl->render_info, sdl->surface);
	sdl->render_info->rect.y += TEXT_Y_SHIFT;
	render_text("run one cycle - N", sdl->render_info, sdl->surface);
	sdl->render_info->rect.y += TEXT_Y_SHIFT;
	render_text("increase / decrease speed - I / D",
						sdl->render_info, sdl->surface);
	sdl->render_info->rect.y += TEXT_Y_SHIFT;
	render_text("pause / play music - P",
						sdl->render_info, sdl->surface);
	sdl->render_info->rect.y += TEXT_Y_SHIFT;
	render_text("stop music - S",
						sdl->render_info, sdl->surface);
	sdl->render_info->rect.y += TEXT_Y_SHIFT;
	render_text("exit game - ESC",
						sdl->render_info, sdl->surface);
	sdl->render_info->rect.y += TEXT_Y_SHIFT;
}

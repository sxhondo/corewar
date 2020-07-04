/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   announce_winner.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 20:00:09 by rgyles            #+#    #+#             */
/*   Updated: 2020/02/01 17:27:23 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"
#include "corewar.h"

static void	set_new_font_size(t_render *render_info)
{
	TTF_Font *font;

	font = render_info->font;
	TTF_CloseFont(font);
	font = TTF_OpenFont(FONT_PATH, FONT_SIZE_ANNOUNCE);
	if (font == NULL)
		exit(error_message("TTF_OpenFont", TTF_GetError()));
	TTF_SetFontStyle(font, TTF_STYLE_BOLD);
	render_info->font = font;
}

/*
** changed fond (its size) in the middle
*/

static void	prepare_announcement(int player, t_sdl *sdl)
{
	SDL_Rect	rect;
	t_render	*render_info;

	rect.x = 2;
	rect.y = 2;
	rect.w = 1350;
	rect.h = 1155;
	SDL_FillRect(sdl->surface, &rect, 0);
	render_info = sdl->render_info;
	set_new_font_size(render_info);
	render_info->back_color = sdl->colors[player + FONT_COLOR];
	render_info->font_color = (SDL_Color) {0, 0, 0x4d, 0};
}

/*
** print player's comment or not?
*/

void		announce_winner(int player, int *play, t_info *info, t_sdl *sdl)
{
	size_t		len;
	char		*winner_name;
	t_render	*render_info;

	prepare_announcement(player, sdl);
	render_info = sdl->render_info;
	render_info->rect.x = 400;
	render_info->rect.y = 300;
	render_text_outline("Winner is:", render_info, sdl);
	winner_name = (info->players)[player - 1].prog_name;
	len = ft_strlen(winner_name);
	if (len > 25)
	{
		winner_name[25] = '\0';
		len = 25;
	}
	render_info->rect.x -= (len - 10) * 20;
	render_info->rect.y += 300;
	render_text_outline(winner_name, render_info, sdl);
	*play = GAME_OVER;
}

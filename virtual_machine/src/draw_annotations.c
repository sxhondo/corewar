/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_annotations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 16:35:59 by rgyles            #+#    #+#             */
/*   Updated: 2020/02/08 13:53:45 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"
#include "corewar.h"

static void	render_player(int i, char *text, t_info *info, t_sdl *sdl)
{
	char name[40];

	ft_bzero(name, 40);
	if (ft_strlen(info->players[i].prog_name) > 38)
		ft_strncpy(name, info->players[i].prog_name, 38);
	else
		ft_strcpy(name, info->players[i].prog_name);
	sdl->render_info->rect.x = PLAYER_X_LOCATION;
	sdl->render_info->font_color = sdl->colors[WHITE];
	render_text(text, sdl->render_info, sdl->surface);
	sdl->render_info->rect.y += 20;
	sdl->render_info->rect.x = PLAYER_NAME_X_LOCATION;
	sdl->render_info->font_color = sdl->colors[i + 2];
	render_text(name, sdl->render_info, sdl->surface);
	sdl->render_info->rect.y += 20;
	sdl->render_info->font_color = sdl->colors[WHITE];
	render_text("last live: -", sdl->render_info, sdl->surface);
	sdl->render_info->rect.y = PLAYER_Y_LOCATION +
						PLAYER_SECTION_HEIGHT * (i + 1);
	update_live(i, 0, sdl);
}

/*
** i = -1 - to save some space
*/

static void	show_players(t_info *info, t_sdl *sdl)
{
	int		i;
	char	*text;

	sdl->render_info->rect.y = PLAYER_Y_LOCATION;
	sdl->render_info->back_color = sdl->colors[BLACK];
	i = -1;
	while (++i < info->count_process)
	{
		if (i == 0)
			text = PLAYER_ONE;
		else if (i == 1)
			text = PLAYER_TWO;
		else if (i == 2)
			text = PLAYER_THREE;
		else
			text = PLAYER_FOUR;
		render_player(i, text, info, sdl);
	}
}

void		draw_annotations(t_info *info, t_sdl *sdl)
{
	sdl->render_info->font_color = sdl->colors[WHITE];
	sdl->render_info->back_color = sdl->colors[BLACK];
	sdl->render_info->rect.x = INFO_X_LOCATION;
	sdl->render_info->rect.y = INFO_Y_LOCATION;
	render_text("cycle - ", sdl->render_info, sdl->surface);
	sdl->render_info->rect.y += TEXT_Y_SHIFT;
	render_text("last_live - ", sdl->render_info, sdl->surface);
	sdl->render_info->rect.y += TEXT_Y_SHIFT;
	render_text("cycle to die - ", sdl->render_info, sdl->surface);
	sdl->render_info->rect.y += TEXT_Y_SHIFT;
	render_text("# of cursors - ", sdl->render_info, sdl->surface);
	sdl->render_info->rect.y += TEXT_Y_SHIFT;
	render_text("count_check - ", sdl->render_info, sdl->surface);
	sdl->render_info->rect.y += TEXT_Y_SHIFT;
	render_text("delay - ", sdl->render_info, sdl->surface);
	show_data(info, sdl);
	udpate_delay(DEFAULT_GAME_SPEED, sdl);
	update_game_status(0, sdl);
	show_players(info, sdl);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_visual_arena.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 17:20:29 by rgyles            #+#    #+#             */
/*   Updated: 2020/02/01 21:25:45 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"
#include "corewar.h"

static void	draw_memory_frame(t_sdl *sdl)
{
	t_square	sq_info;

	sq_info = (t_square) {0, WIN_HEIGHT - 1, WIN_WIDTH - 445, 0, 0xFFA500};
	draw_square(&sq_info, sdl->img_data);
	sq_info = (t_square) {WIN_WIDTH - 444, WIN_HEIGHT - 500,
									WIN_WIDTH - 1, 0, 0x33CCFF};
	draw_square(&sq_info, sdl->img_data);
	sq_info = (t_square) {WIN_WIDTH - 444, WIN_HEIGHT - 1,
						WIN_WIDTH - 1, WIN_HEIGHT - 500, 0x6600CC};
	draw_square(&sq_info, sdl->img_data);
}

/*
** draw range from i to end
** end_of_row detects last index(one dimension)
** on the current row(two dimension)
*/

static void	draw_range(int i, int end, unsigned char *arena, t_sdl *sdl)
{
	int			end_of_row;
	int			row;
	t_render	*render_info;
	SDL_Surface	*surface;

	render_info = sdl->render_info;
	surface = sdl->surface;
	row = i / 64;
	end_of_row = (row + 1) * 64;
	while (1)
	{
		while (i < end_of_row)
		{
			if (i == end)
				return ;
			draw_byte(arena[i++], render_info, surface);
			render_info->rect.x += NIBBLE_WIDTH;
		}
		render_info->rect.y += NIBBLE_HEIGHT;
		render_info->rect.x = NIBBLE_X_SHIFT;
		end_of_row = (++row + 1) * 64;
		i = end_of_row - 64;
	}
}

/*
** increment start, as cursor will be initialized in another function
*/

static void	draw_arena(t_processes *processes, t_info *info, t_sdl *sdl)
{
	int	start;
	int end;
	int	player;

	player = 1;
	while (processes != NULL)
	{
		start = processes->index;
		end = start + ((info->players)[player - 1]).prog_size;
		create_cursor(start, sdl->replica[start] - 1, sdl);
		++start;
		set_nibble_for_render(start, CODE, player, sdl);
		draw_range(start, end, info->arena, sdl);
		set_nibble_for_render(end, EMPTY, player, sdl);
		if (processes->prev == NULL)
			draw_range(end, MEM_SIZE, info->arena, sdl);
		else
			draw_range(end, (processes->prev)->index, info->arena, sdl);
		++player;
		processes = processes->prev;
	}
}

/*
** while loop to go back to first plater
*/

void		initialize_visual_arena(t_sdl *sdl, t_info *info)
{
	t_processes	*processes;

	processes = info->processes;
	draw_memory_frame(sdl);
	while (processes->next != NULL)
		processes = processes->next;
	set_replica(processes, info, sdl);
	draw_arena(processes, info, sdl);
	draw_annotations(info, sdl);
	draw_game_controls(sdl);
	SDL_UpdateWindowSurface(sdl->window);
}

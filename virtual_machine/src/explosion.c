/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   explosion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 17:22:02 by rgyles            #+#    #+#             */
/*   Updated: 2020/02/01 17:12:12 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sdl_struct.h"
#include "visual.h"
#include "corewar.h"

/*
** clean only arena
*/

void		refresh_arena(t_info *info, t_sdl *sdl)
{
	int			location;
	t_processes	*processes;

	SDL_FillRect(sdl->surface, &(SDL_Rect) {2, 2, 1350, 1155}, 0);
	location = 0;
	while (location < 4096)
		update_byte(location++, sdl);
	processes = info->processes;
	while (processes != NULL)
	{
		create_cursor(processes->index, -processes->reg[0] - 1, sdl);
		processes = processes->next;
	}
}

/*
** 8 is the shift to move to nibble's center
** rect to redraw region, 5 x 5 square
*/

t_explosion	*create_explosion(int location)
{
	int			start;
	t_explosion *e;

	e = malloc(sizeof(t_explosion));
	ft_bzero(e, sizeof(e));
	start = location - 64 * 2 - 2;
	e->rect.x = NIBBLE_X_SHIFT + NIBBLE_WIDTH * (start % 64);
	e->rect.y = NIBBLE_Y_SHIFT + NIBBLE_HEIGHT * (start / 64);
	e->rect.w = NIBBLE_WIDTH * 5;
	e->rect.h = NIBBLE_HEIGHT * 5;
	e->start = start;
	e->location = location;
	e->x = NIBBLE_X_SHIFT + NIBBLE_WIDTH * (location % 64) + 8;
	e->y = NIBBLE_Y_SHIFT + NIBBLE_HEIGHT * (location / 64) + 8;
	e->next = NULL;
	return (e);
}

void		add_explosion(t_explosion *e, t_explosion **head)
{
	if (*head == NULL)
		*head = e;
	else
	{
		e->next = *head;
		*head = e;
	}
}

void		remove_explosion(t_explosion *e, t_explosion **head)
{
	t_explosion *cur;

	cur = *head;
	while (cur != e)
		cur = cur->next;
	*head = e->next;
	free(e);
}

/*
** MAGIC!
** rect height and width are for each particle
** rect x and y division controls the size of explosion
** addition controls position
** inner if check if particals stay within arena
*/

void		draw_explosion(t_explosion *e, t_sdl *sdl)
{
	int			i;
	SDL_Rect	rect;

	rect = (SDL_Rect) {0, 0, 2, 1};
	while (e)
	{
		i = 256 * !(e->n);
		while (i)
			e->q[--i] = rand() % 65536 * 9.5874e-5;
		if (++e->n == 43)
			remove_explosion(e, &sdl->head_explosion);
		else
		{
			i = -1;
			while (++i < 256)
			{
				rect.x = e->x + cos(e->q[i]) * e->q[i - 1] * e->n / 10;
				rect.y = e->y + sin(e->q[i]) * e->q[i - 1] * e->n / 10;
				if (rect.x > 2 && rect.x < 1351 && rect.y > 2 && rect.y < 1157)
					SDL_FillRect(sdl->surface, &rect, 0xFFFFFF << e->r);
				e->r++;
			}
		}
		e = e->next;
	}
}

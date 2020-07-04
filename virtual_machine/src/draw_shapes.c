/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_shapes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 15:15:47 by rgyles            #+#    #+#             */
/*   Updated: 2020/01/11 18:51:40 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"

void	draw_vertical_line(int x, t_square *sq_info, int *img_data)
{
	int	y;
	int	h;
	int	color;

	y = sq_info->y1;
	h = sq_info->y0;
	color = sq_info->color;
	while (y < h)
	{
		img_data[y * WIN_WIDTH + x] = color;
		++y;
	}
}

void	draw_horizontal_line(int y, t_square *sq_info, int *img_data)
{
	int	x;
	int	w;
	int	color;

	x = sq_info->x0;
	w = sq_info->x1;
	color = sq_info->color;
	while (x < w)
	{
		img_data[y * WIN_WIDTH + x] = color;
		++x;
	}
}

void	draw_square(t_square *sq_info, int *img_data)
{
	draw_vertical_line(sq_info->x0, sq_info, img_data);
	draw_vertical_line(sq_info->x0 + 1, sq_info, img_data);
	draw_vertical_line(sq_info->x1, sq_info, img_data);
	draw_vertical_line(sq_info->x1 - 1, sq_info, img_data);
	draw_horizontal_line(sq_info->y1, sq_info, img_data);
	draw_horizontal_line(sq_info->y1 + 1, sq_info, img_data);
	draw_horizontal_line(sq_info->y0, sq_info, img_data);
	draw_horizontal_line(sq_info->y0 - 1, sq_info, img_data);
}

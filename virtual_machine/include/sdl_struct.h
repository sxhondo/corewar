/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_struct.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 12:26:43 by rgyles            #+#    #+#             */
/*   Updated: 2020/01/25 13:32:12 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SDL_STRUCT_H
# define SDL_STRUCT_H

# include "SDL.h"
# include "SDL_ttf.h"
# include "SDL_mixer.h"

typedef struct	s_render
{
	SDL_Rect	rect;
	SDL_Color	font_color;
	SDL_Color	back_color;
	TTF_Font	*font;
}				t_render;

typedef struct	s_explosion
{
	int					n;
	int					r;
	int					x;
	int					y;
	int					start;
	int					location;
	double				q[256];
	SDL_Rect			rect;
	struct s_explosion	*next;
}				t_explosion;

typedef struct	s_sdl
{
	int				*img_data;
	unsigned char	*arena;
	unsigned char	*replica;
	SDL_Window		*window;
	SDL_Surface		*surface;
	SDL_Color		colors[11];
	Mix_Music		*main_theme;
	Mix_Chunk		*live_effect;
	Mix_Chunk		*birth_effect;
	TTF_Font		*outline_font;
	t_render		*render_info;
	t_explosion		*head_explosion;
}				t_sdl;

#endif

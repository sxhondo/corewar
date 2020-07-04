/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgyles <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 16:09:49 by rgyles            #+#    #+#             */
/*   Updated: 2020/02/08 13:32:01 by rgyles           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUAL_H
# define VISUAL_H

# include "sdl_struct.h"

# define WIN_HEIGHT 1160
# define WIN_WIDTH 1800

# define FONT_PATH "fonts/FreeMono.ttf"
# define FONT_SIZE 15
# define FONT_SIZE_ANNOUNCE 70
# define OUTLINE 2

# define NIBBLE_X_SHIFT 7
# define NIBBLE_Y_SHIFT 5

# define NIBBLE_WIDTH 21
# define NIBBLE_HEIGHT 18

# define BLACK 0
# define WHITE 1
# define YELLOW 2
# define BLUE 3
# define GREEN 4
# define RED 5
# define YELLOW_BACK 6
# define BLUE_BACK 7
# define GREEN_BACK 8
# define RED_BACK 9
# define GREY 10

# define FONT_COLOR 1
# define BACK_COLOR 5

# define EMPTY 0
# define CURSOR 1
# define CODE 2

# define GAME_STATUS_X_LOCATION 1400
# define GAME_STATUS_Y_LOCATION 30
# define GAME_STATUS_WIDTH 70

# define PLAYER_ONE "Player 1: "
# define PLAYER_TWO "Player 2: "
# define PLAYER_THREE "Player 3: "
# define PLAYER_FOUR "Player 4: "

# define PLAYER_X_LOCATION 1380
# define PLAYER_Y_LOCATION 200
# define PLAYER_NAME_X_LOCATION 1400
# define PLAYER_NAME_Y_LOCATION 140
# define PLAYER_SECTION_HEIGHT 100

# define INFO_X_LOCATION 1420
# define INFO_Y_LOCATION 50

# define TEXT_Y_SHIFT 20

# define DATA_X_LOCATION 1570
# define DATA_Y_LOCATION 50

# define LIVE_X_LOCATION 1500

# define CONTROLS_Y_LOCATION 700

# define SDL_DATA_X_LOCATION 1570
# define SDL_DATA_Y_LOCATION 150
# define SDL_DATA_WIDTH 90

# define DEFAULT_GAME_SPEED 100

# define GAME_PAUSED 0
# define GAME_RUNNING 1
# define GAME_SHOW -1
# define GAME_OVER -2

# define RED_TERM "\033[0;31m"
# define NC_TERM "\033[0m"

/*
** x0, y0 - lower left corner
** x1, y1 - top right corner
*/

typedef struct	s_square
{
	int	x0;
	int	y0;
	int	x1;
	int y1;
	int	color;
}				t_square;

typedef struct	s_controls
{
	int	play;
	int	speed;
	int	show_time;
	int	seed;
}				t_controls;

int				init_sdl(unsigned char *arena, t_sdl *sdl);
int				error_message(const char *subject, const char *message);
void			draw_byte(unsigned char byte, t_render *render_info,
												SDL_Surface *surface);
void			set_nibble_for_render(int location, int type, int player,
																t_sdl *sdl);
void			draw_byte(unsigned char byte, t_render *render_info,
												SDL_Surface *surface);
void			int_to_char(int number, char *str);
void			udpate_delay(int delay, t_sdl *sdl);
void			draw_game_controls(t_sdl *sdl);
void			draw_square(t_square *sq_info, int *img_data);
void			update_game_status(int status, t_sdl *sdl);
void			epilepsy(int seed, t_render *render_info,
								SDL_Surface *surface, t_sdl *sdl);
void			render_text(char *text, t_render *render_info,
											SDL_Surface *surface);
void			render_text_outline(char *text,
					t_render *render_info, t_sdl *sdl);
t_explosion		*create_explosion(int location);
void			add_explosion(t_explosion *e, t_explosion **head);
void			remove_explosion(t_explosion *e, t_explosion **head);
void			draw_explosion(t_explosion *e, t_sdl *sdl);

#endif

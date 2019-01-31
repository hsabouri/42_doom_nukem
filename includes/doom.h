/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 16:14:26 by hugo              #+#    #+#             */
/*   Updated: 2019/01/30 16:30:09 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_H
# define DOOM_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <math.h>
# include <SDL2/SDL.h>
# include <SDL2/SDL_ttf.h>
# include <float.h>

# include <libft.h>
# include <vec.h>
# include <graphic.h>
# include <physic.h>
# include <editor.h>

# define N_KEY 284
# define N_BUTTON 5

# define MIN(a, b) ((a < b) ? a : b)
# define MAX(a, b) ((a > b) ? a : b)

# define LOOK_SPEED 0.01

typedef struct			s_event
{
	int16_t		x;
	int16_t		y;
	int16_t		old_x;
	int16_t		old_y;
	int16_t		wheel;
	u_int8_t	quit;
	u_int8_t	mouse[N_BUTTON];
	u_int8_t	mouse_click[N_BUTTON];
	u_int8_t	keys[N_KEY]; //must be last
}						t_event;

typedef struct			s_sdl
{
	SDL_Window		*win;
	SDL_Texture		*buf;
	SDL_Renderer	*renderer;
	TTF_Font		*font;
}						t_sdl;

typedef struct			s_env
{
	t_game		game;
	int			toggle_editor;
	t_editor	editor;
	t_color		*current_buffer;
	t_sdl		sdl;
	t_event		events; //must be last
}						t_env;

t_env					game_loop(t_env env, size_t frame);
t_env					editor_loop(t_env env, size_t frame);

t_event					capture_events(t_event events, t_env *env);
t_event					init_events(void);
t_ph					update_mouse(t_event *events, t_ph player_physic);
t_event					reset_clicks(t_event events);

void					bresenham(t_color *buff, t_pix a, t_pix b, \
						t_color color);

t_game					physic(t_game game, t_event events);
t_player				player_physic(t_event events, t_game game);

t_pix					text(const char *str, t_pix pos, t_sdl sdl);


/*
** EDITOR
*/

t_vec2					point_from_mouse(t_event events, t_editor editor);
ssize_t					select_point(t_game game, t_editor editor,\
						t_event events);
ssize_t					select_wall(t_game game, t_editor editor,\
						t_event events);
t_editor				select_multi_points(t_editor editor,\
						t_event events, ssize_t point);
void					legend_text(t_sdl sdl);
void					legend_graphic(t_color *buf);
t_game					game_editing(t_game game, t_event events,\
						t_player player);
t_game					player_properties(t_game game, t_event events);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 16:14:26 by hugo              #+#    #+#             */
/*   Updated: 2019/01/05 12:15:31 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_H
# define DOOM_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <math.h>
# include <SDL2/SDL.h>
# include <float.h>

# include <libft.h>
# include <vec.h>
# include <graphic.h>

# define N_KEY 284

# define MIN(a, b) ((a < b) ? a : b)
# define MAX(a, b) ((a > b) ? a : b)
# define SPEED_REDUCE 30
# define LOOK_SPEED 0.01

typedef struct			s_event
{
	int16_t		x;
	int16_t		y;
	int16_t		old_x;
	int16_t		old_y;
	int8_t		left;
	int8_t		right;
	u_int8_t	quit;
	u_int8_t	keys[N_KEY]; //must be last
}						t_event;

typedef struct			s_sdl
{
	SDL_Window		*win;
	SDL_Texture		*buf;
	SDL_Renderer	*renderer;
}						t_sdl;

typedef struct			s_env
{
	t_game		game;
	t_color		*current_buffer;
	t_sdl		sdl;
	t_event		events; //must be last
}						t_env;

t_event					capture_events(t_event events);
t_event					init_events(void);

void					bresenham(t_color *buff, t_pix a, t_pix b, \
						t_color color);

t_game					physic(t_game game, t_event events);
t_player				player_physic(t_event events, t_game game);
int						collision(t_vec3 next_pos, t_game game);

t_ph					update_mouse(t_event *events, t_ph player_physic);

#endif

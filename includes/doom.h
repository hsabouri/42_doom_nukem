/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 16:14:26 by hugo              #+#    #+#             */
/*   Updated: 2018/12/29 17:51:22 by hsabouri         ###   ########.fr       */
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

# define WIDTH 640
# define HEIGHT 480
# define N_KEY 284

# define MIN(a, b) ((a < b) ? a : b)
# define MAX(a, b) ((a > b) ? a : b)

typedef struct			s_event
{
	u_int8_t	quit;
	u_int8_t	keys[N_KEY];
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
#endif

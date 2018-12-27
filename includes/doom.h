/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 16:14:26 by hugo              #+#    #+#             */
/*   Updated: 2018/12/27 17:55:08 by hugo             ###   ########.fr       */
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

/*
typedef struct			s_texture
{
	t_color		*data;
	uint16_t	width;
	uint16_t	height;
	int			transparent;
}						t_texture;
*/

typedef struct			s_ph
{
	float		gravity;
	float		height;
	t_vec3		pos;
	t_vec3		speed;
	t_vec3		speed_max;
	t_vec2		look;
}						t_ph;

/*
typedef enum			u_wtype
{
	GUN,
	MACHINE_GUN,
	SNIPER,
	PLASMA_RIFLE,
	GRENADE
}						t_wtype;

typedef struct			s_weapon
{
	t_wtype		type;
	float		damage;
	uint16_t	cooldown;
	uint16_t	munitions;
}						t_weapon;
*/

typedef struct			s_player
{
	t_ph		ph_enabled;
	//float		life;
	//float		armor;
	//t_array		inventory;
	//uint8_t		equiped;
	//t_weapon	weapons[5];
}						t_player;

typedef struct			s_portal
{
	u_int32_t	from_sector;
	u_int32_t	to_sector;
	u_int32_t	from_wall;
	u_int32_t	to_wall;
	u_int32_t	a;
	u_int32_t	b;
}						t_portal;

typedef struct			s_wall
{
	int32_t		portal;
	u_int32_t	a;
	u_int32_t	b;
	//u_char		texture;
	//u_char		transparent;
}						t_wall;

typedef struct			s_sector
{
	u_int32_t	start;
	u_int32_t	number;
	float		floor;
	float		ceiling;
	//float		luminosity;
}						t_sector;

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

typedef struct			s_game
{
	t_player	player;
	t_array		sectors;
	t_array		walls;
	t_array		portals;
	t_array		points;
	t_color		*current_buffer;
	t_sdl		sdl;
	t_event		events; //must be last
}						t_game;

t_event					capture_events(t_event events);
t_event					init_events(void);

void					display_wall(void *wall, void *game);

t_game					generate_map(t_game game);

#endif

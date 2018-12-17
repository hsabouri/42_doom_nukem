/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 16:14:26 by hugo              #+#    #+#             */
/*   Updated: 2018/12/16 18:32:22 by hugo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_H
# define DOOM_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <SDL2/SDL.h>
# include <vec.h>
# include <libft.h>
# include <math.h>

# ifndef M_PI
#  define M_PI 3.141592653
# endif

# define WIDTH 640
# define HEIGHT 480
# define N_KEY 284

# define RED     "\x1b[31m"
# define GREEN   "\x1b[32m"
# define YELLOW  "\x1b[33m"
# define BLUE    "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN    "\x1b[36m"
# define RESET   "\x1b[0m"

typedef struct			s_color
{
	u_int8_t	b;
	u_int8_t	g;
	u_int8_t	r;
	u_int8_t	a;
}						t_color;

typedef struct			s_pix
{
	u_int32_t	x;
	u_int32_t	y;
}						t_pix;

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
	t_vec2		look_max;
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
	u_int8_t	keys[N_KEY];
	u_int8_t	quit;
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
	//t_array		entities;
	t_array		sectors;
	t_array		walls;
	t_array		portals;
	t_array		points;
	t_sdl		sdl;
	//t_array		textures;
	t_event		events; //must be last
}						t_game;

void					exit_error(const char *error);

t_event					capture_events(t_event events);
t_event					init_events(void);

void					line(t_color *buf, t_vec2 a, t_vec2 b, t_color color);

#endif

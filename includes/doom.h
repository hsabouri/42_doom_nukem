/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 16:14:26 by hugo              #+#    #+#             */
/*   Updated: 2018/11/27 18:12:07 by arusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_H
# define DOOM_H
# include <stdlib.h>
# include <sys/types.h>
# include <SDL2/SDL.h>
# include <SDL2/SDL_image.h>
# include <SDL2/SDL_ttf.h>
# include <SDL2/SDL_mixer.h>

# include <fixed_math.h>
# include <libft.h>

typedef struct			s_color
{
	u_char		b;
	u_char		g;
	u_char		r;
	u_char		a;
}						t_color;

typedef struct			s_texture
{
	t_color		*data;
	uint16_t	width;
	uint16_t	height;
	int			transparent;
}						t_texture;

typedef struct			s_ph
{
	t_fixed		gravity;
	t_fixed		height;
	t_vec4		pos;
	t_vec4		speed;
	t_vec4		speed_max;
	t_vec2		look;
	t_vec2		look_max;
}						t_ph;

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
	t_fixed		damage;
	uint16_t	cooldown;
	uint16_t	munitions;
}						t_weapon;

typedef struct			s_player
{
	t_ph		ph_enabled;
	t_fixed		life;
	t_fixed		armor;
	t_array		inventory;
	uint8_t		equiped;
	t_weapon	weapons[5];
}						t_player;

typedef struct			s_portal
{
	u_int32_t	step;
	u_int32_t	ceil;
	u_int32_t	a;
	u_int32_t	b;
}						t_portal;

typedef struct			s_wall
{
	u_int32_t	portal;
	u_int32_t	a;
	u_int32_t	b;
	u_char		texture;
	u_char		transparent;
}						t_wall;

typedef struct			s_sector
{
	u_int32_t	begin;
	u_int32_t	number;
	t_fixed		floor;
	t_fixed		ceiling;
	t_fixed		luminosity;
}						t_sector;

typedef struct			s_game
{
	t_player	player;
	t_array		entities;
	t_array		sectors;
	t_array		walls;
	t_array		portals;
	t_array		points;
	t_array		textures;
}						t_game;

#endif

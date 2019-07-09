/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 17:47:17 by hsabouri          #+#    #+#             */
/*   Updated: 2019/07/06 15:42:26 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <math.h>
# include <float.h>
# include <libft.h>
# include <vec.h>
# include <tga.h>
# include "./weapons.h"

# ifndef LOAD_SAVE_H
#  include <SDL2/SDL_mixer.h>
# endif

# define ANIMATION_SPEED 0.5

typedef struct		s_animation
{
	float		*to_animate;
	float		target;
}					t_animation;

typedef enum		e_mode
{
	SKYBOX,
	TILING,
	NO_TILING
}					t_mode;

typedef enum		e_col_mode
{
	COL_ENTITY,
	COL_INTERACT
}					t_col_mode;

typedef enum		e_entity_type
{
	PLAYER = 0,
	GUN_MARINE = 1,
	SMG_MARINE = 2,
	RACLURE = 3,
	RED_MARINE = 4,
	RED_KEY_CARD = 5,
	BLUE_KEY_CARD = 6,
	GREEN_KEY_CARD = 7,
	PURPLE_KEY_CARD = 8,
	APPLE = 9,
	FISH = 10,
	MEAT = 11,
	MEDIPACK = 12,
	AMMO = 13,
	CLOSE_RED = 14,
	CLOSE_BLUE = 15,
	CLOSE_GREEN = 16,
	CLOSE_PURPLE = 17,
	OPEN_RED = 18,
	OPEN_BLUE = 19,
	OPEN_GREEN = 20,
	OPEN_PURPLE = 21,
	LAMP = 22,
	CEIL_LAMP = 23,
	PLANT_1 = 24,
	PLANT_2 = 25,
	PLANT_3 = 26,
	PLANT_4 = 27,
	TRASH_1 = 28,
	TRASH_2 = 29,
	GUN = 30,
	SMG = 31,
	SHOTGUN = 32,
	REVOLVER = 33,
	NYAN_GUN = 34
}					t_entity_type;

typedef struct		s_mat
{
	t_fvec2			pos;
	t_fvec2			sca;
	t_color			color;
	t_img			*texture;
	t_mode			mode;
	t_color			filter;
	int				frozen;
	struct s_mat	*overlay;
}					t_mat;

typedef struct		s_ph
{
	float		gravity;
	float		height;
	float		radius;
	float		rad_inter;
	t_vec3		pos;
	t_vec3		speed;
	t_vec3		speed_max;
	float		look_h;
	t_fixed		look_v;
	u_int32_t	sector_id;
	u_int32_t	jump;
	char		fly;
}					t_ph;

typedef struct		s_entity
{
	int				id;
	t_ph			physic;
	t_ph			spawn;
	t_array			*mat;
	t_entity_type	type;
	float			life;
	int				data;
}					t_entity;

typedef struct		s_player
{
	t_entity	my_entity;
	u_int32_t	weapons[2];
	u_int32_t	secondary;
	u_int16_t	equiped;
	u_int16_t	is_shooting;
	t_array		inventory;
}					t_player;

typedef struct		s_portal
{
	u_int32_t	from_sector;
	u_int32_t	to_sector;
	u_int32_t	from_wall;
	u_int32_t	to_wall;
	t_mat		*mat;
	int			blocking;
}					t_portal;

typedef struct		s_wall
{
	t_fvec2		tex_pos;
	int32_t		portal;
	u_int32_t	a;
	u_int32_t	b;
	t_mat		*mat;
	t_vec2		left_z;
	t_vec2		right_z;
}					t_wall;

typedef struct		s_sector
{
	u_int32_t	start;
	u_int32_t	number;
	size_t		sector_id;
	t_vec3		floor;
	t_vec3		ceiling;
	t_vec3		floor_b;
	t_vec3		ceiling_b;
	t_color		ambient;
	t_mat		*ceiling_mat;
	t_mat		*floor_mat;
	t_fvec2		tex_pos;
	t_vec2		center;
	int			clock;
}					t_sector;

typedef struct		s_music
{
	Mix_Music	*music;
}					t_music;

typedef	struct		s_sound
{
	Mix_Chunk	*sound;
}					t_sound;

typedef struct		s_chunk
{
	size_t		chunk_id;
	float		volume;
}					t_chunk;

typedef enum		e_col_type
{
	INTERACT,
	DIRECT
}					t_col_type;

typedef struct		s_col_event
{
	t_col_type		type;
	size_t			e_id;
}					t_col_event;

typedef struct		s_game
{
	t_player		player;
	t_array			col_events;
	t_entity		*entities;
	size_t			nentities;
	size_t			unique_e_id;
	t_entity		*classes;
	size_t			nclasses;
	t_sector		*sectors;
	size_t			nsectors;
	t_wall			*walls;
	size_t			nwalls;
	size_t			nuwalls;
	t_portal		*portals;
	size_t			nportals;
	t_vec2			*points;
	size_t			npoints;
	t_mat			*materials;
	size_t			nmaterials;
	t_img			*textures;
	size_t			ntextures;
	t_array			*multi_mats;
	size_t			nmulti_mats;
	t_weapon		*weapons;
	size_t			nweapons;
	t_array			music;
	size_t			played_music;
	t_array			sounds;
	t_array			animations;
	t_array			chunks;
	size_t			frame;
	u_int32_t		*id_buf;
}					t_game;

t_game				generate_map(void);

#endif

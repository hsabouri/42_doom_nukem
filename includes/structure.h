/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 17:47:17 by hsabouri          #+#    #+#             */
/*   Updated: 2019/06/17 14:36:26 by hsabouri         ###   ########.fr       */
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
#	include <SDL2/SDL_mixer.h>
# endif

# define ANIMATION_SPEED 1.0
# define ABS(v) ((v >= 0) ? v : -v)

typedef enum		e_mode
{
	SKYBOX,
	TILING,
	NO_TILING
}					t_mode;

typedef enum		s_col_mode
{
	COL_ENTITY,
	COL_INTERACT
}					t_col_mode;

typedef enum		s_entity_type
{
	PLAYER,
	GUN_MARINE,
	SMG_MARINE,
	BLACK_MARINE,
	RED_MARINE,
	GREEN_KEY_CARD,
	BLUE_KEY_CARD,
	RED_KEY_CARD,
	PURPLE_KEY_CARD,
	APPLE,
	FISH,
	MEAT,
	MEDIPACK,
	AMMO
}					t_entity_type;

typedef struct		s_animation
{
	float		*to_animate;
	float		target;
}					t_animation;

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
}						t_ph;

typedef enum		e_condition
{
	TRIGGER_SEE = 0x1,
	TRIGGER_TOUCH = 0x2,
	TRIGGER_INTERACT = 0x3,
	TRIGGER_SECTOR = 0x4,
	TRIGGER_SHOT = 0x0
}					t_condition;

typedef enum		e_action_c
{
	ACTION_KILL = 0x1,
	ACTION_H_DOWN = 0x2,
	ACTION_H_UP = 0x3,
	ACTION_ADD_INV = 0x4,
	ACTION_ANIMATE = 0x5,
}					t_action_c;

struct s_game_event;


typedef struct		s_entity
{
	int				id;
	t_ph			physic;
	t_ph			spawn;
	t_array			*mat;
	t_entity_type	type;
	t_plist	self_events;
	float life;
	// float  armor;
	// t_weapon weapons;
	int 			damage;
}					t_entity;

typedef struct		s_action
{
	t_vec2			pos;
	t_entity		*target;
	t_action_c		action_type;
	int				num;
}					t_action;

typedef struct		s_trigger
{
	t_entity	e_actif;
	t_condition	condi;
	t_entity	e_passif;
}					t_trigger;

typedef struct		s_game_event
{
	t_pelem		elem;
	t_trigger	trigger;
	t_action	 action;
}					t_game_event;


typedef struct		s_player
{
	t_entity	my_entity;
	size_t		life;
	u_int32_t	weapons[2];
	u_int32_t	secondary;
	u_int32_t	equiped;
	t_array		inventory;
	// float		armor;
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
	// float		floor_a;
	// float		floor_b;
	t_vec3		floor;
	t_vec3		ceiling;
	// float		ceiling_a;
	// float		ceiling_b;
	t_color		ambient;
	t_mat		*ceiling_mat;
	t_mat		*floor_mat;
	t_fvec2		tex_pos;
	t_vec2		center; // t_vec3 position
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
	u_int32_t	volume;
}					t_chunk;

typedef struct		s_game
{
	t_player		player;
	t_plist 		waiting_events;
	t_array			log;
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
	t_array			animations;
	t_array			music;
	size_t			played_music;
	t_array			sounds;
	t_array			chunks;
	size_t			frame;
	u_int32_t		*id_buf;
}					t_game;

t_game				generate_map(void);

#endif

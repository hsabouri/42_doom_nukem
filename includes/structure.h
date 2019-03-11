/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbougero <lbougero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 17:47:17 by hsabouri          #+#    #+#             */
<<<<<<< HEAD
<<<<<<< HEAD
/*   Updated: 2019/04/25 11:57:27 by hsabouri         ###   ########.fr       */
=======
=======
>>>>>>> need collision
<<<<<<< HEAD
/*   Updated: 2019/03/19 16:02:37 by hsabouri         ###   ########.fr       */
=======
/*   Updated: 2019/03/11 18:44:25 by lbougero         ###   ########.fr       */
>>>>>>> trigger en cours
<<<<<<< HEAD
>>>>>>> trigger en cours
=======
=======
/*   Updated: 2019/03/11 18:46:30 by lbougero         ###   ########.fr       */
>>>>>>> need collision
>>>>>>> need collision
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

typedef struct		s_mat
{
	t_fvec2			pos;
	t_fvec2			sca;
	t_color			color;
	t_img			*texture;
	t_mode			mode;
	t_color			filter;
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

<<<<<<< HEAD
=======

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


typedef enum	e_condition
{
	TRIGGER_SEE = 0x1,
	TRIGGER_TOUCH = 0x2,
	TRIGGER_INTERACT = 0x3,
	TRIGGER_NO = 0x0
}				t_condition;


>>>>>>> trigger en cours
typedef struct		s_entity
{
	t_ph		physic;
	t_ph		spawn;
	t_array		mat;
	//float life;
	//float  armor;
	//t_weapon weapons;
	int 		damage;
}					t_entity;

<<<<<<< HEAD
=======
typedef struct		s_trigger
{
	t_entity	e_actif;
	t_condition	condi;
	t_entity	e_passif;
}					t_trigger;

typedef struct		s_game_event
{
	t_trigger	 trigger;
	// int			is_trigger;
	// t_action	 action;
}					t_game_event;


>>>>>>> trigger en cours
typedef struct		s_player
{
	t_ph		physic;
	t_ph		spawn;
<<<<<<< HEAD
	size_t		life;
	u_int32_t	weapons[2];
	u_int32_t	secondary;
	u_int32_t	equiped;
	t_array		inventory;
	// float		armor;
=======
	//float		life;
	//float		armor;
	//t_array		inventory;
	//uint8_t		equiped;
	//t_weapon	weapons[5];
>>>>>>> trigger en cours
}					t_player;

typedef struct		s_portal
{
	u_int32_t	from_sector;
	u_int32_t	to_sector;
	u_int32_t	from_wall;
	u_int32_t	to_wall;
	u_int32_t	a;
	u_int32_t	b;
	t_mat		*mat;
}					t_portal;

typedef struct		s_wall
{
	t_fvec2		tex_pos;
	int32_t		portal;
	u_int32_t	a;
	u_int32_t	b;
	t_mat		*mat;
}					t_wall;

typedef struct		s_sector
{
	u_int32_t	start;
	u_int32_t	number;
	size_t		sector_id;
	float		floor;
	float		ceiling;
	t_color		ambient;
	t_mat		*ceiling_mat;
	t_mat		*floor_mat;
	t_fvec2		tex_pos;
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
	
	t_game_event		*events;
	size_t				nevents;

	t_game_event 	*waiting_events;
	size_t			nwaiting_events;

	t_trigger	*log;

	t_entity	*entities;
	size_t		nentities;
	
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
	t_weapon		*weapons;
	size_t			nweapons;
	t_array			music;
	size_t			played_music;
	t_array			sounds;
	t_array			chunks;
	size_t			frame;
	u_int32_t		*id_buf;
}					t_game;

t_game				generate_map(void);

#endif

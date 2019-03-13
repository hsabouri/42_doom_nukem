/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 17:47:17 by hsabouri          #+#    #+#             */
/*   Updated: 2019/03/11 13:29:34 by hsabouri         ###   ########.fr       */
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

# ifndef LOAD_SAVE_H
#  include <SDL2/SDL_mixer.h>
# endif

typedef enum		e_mode
{
	SKYBOX,
	TILING,
	NO_TILING
}					t_mode;

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
	t_vec3		pos;
	t_vec3		speed;
	t_vec3		speed_max;
	float		look_h;
	t_fixed		look_v;
	u_int32_t	sector_id;
	u_int32_t	jump;
    char		fly;
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

typedef struct		s_player
{
	t_ph		physic;
	t_ph		spawn;
	//float		life;
	//float		armor;
	//t_array		inventory;
	//uint8_t		equiped;
	//t_weapon	weapons[5];
}					t_player;

typedef struct		s_entity
{
	t_ph		physic;
	t_ph		spawn;
	t_mat		*mat;
	//float life;
	//float  armor;
	//t_weapon weapons;
	int 		damage;
}					t_entity;

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

# ifndef LOAD_SAVE_H
typedef struct		s_music
{
	Mix_Music	*music;
}					t_music;

typedef	struct		s_sound
{
	Mix_Chunk	*sound;
}					t_sound;
# else
typedef struct		s_music
{
	size_t	music;
}					t_music;

typedef	struct		s_sound
{
	size_t	sound;
}					t_sound;
# endif

typedef struct		s_chunk
{
	size_t	chunk_id;
	char	volume;
}					t_chunk;

typedef struct		s_game
{
	t_player		player;
	t_sector		*sectors;
	size_t			nsectors;
	t_wall			*walls;
	size_t			nwalls;
	t_portal		*portals;
	size_t			nportals;
	t_vec2			*points;
	size_t			npoints;
	t_entity		*entities;
	size_t			nentities;
	t_mat			*materials;
	size_t			nmaterials;
	t_img			*textures;
	size_t			ntextures;
	t_music			*music;
	size_t			nmusic;
	size_t			played_music;
	t_sound			*sounds;
	size_t			nsounds;
	t_array			chunks;
	size_t			frame;
	u_int32_t		*id_buf;
}					t_game;

t_game				generate_map(t_game game);

#endif

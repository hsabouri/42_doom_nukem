/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure_clone.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 15:42:51 by hsabouri          #+#    #+#             */
/*   Updated: 2019/07/06 15:42:52 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_CLONE_H
# define STRUCTURE_CLONE_H

# define PLAYER_MAGIC	0xDEADBABE
# define GAME_MAGIC		0xDEAD10C4
# define MAT_MAGIC		0x0D15EA5E
# define POINT_MAGIC	0x8BADF00D
# define WALL_MAGIC		0x1B16B00B
# define SECTOR_MAGIC	0xCAFED00D
# define PORTAL_MAGIC	0xC11BE
# define ENTITY_MAGIC	0xFEEEFEEE
# define TEXT_MAGIC		0xFEE1DEAD
# define MUSIC_MAGIC	0xDEFEC8ED
# define SOUND_MAGIC	0xDEADBEEF
# define EVENT_MAGIC	0xD0D0CACA

# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <vec.h>
# include <libft.h>

typedef struct		s_c_img
{
	size_t		magic;
	u_int32_t	width;
	u_int32_t	height;
	size_t		content;
	u_int32_t	edit;
}					t_c_img;

typedef struct		s_c_mat
{
	size_t			magic;
	t_fvec2			pos;
	t_fvec2			sca;
	t_color			color;
	ssize_t			texture;
	t_mode			mode;
	t_color			filter;
	int				frozen;
	ssize_t			overlay;
}					t_c_mat;

typedef struct		s_c_weapon
{
	size_t		magic;
	int32_t		name;
	u_int32_t	type;
	u_int32_t	ammo;
	u_int32_t	ammo_max;
	u_int32_t	damage;
	u_int32_t	cadence;
	int32_t		type_shot;
	ssize_t		sprite[16];
	u_int32_t	decal;
}					t_c_weapon;

typedef struct		s_c_ph
{
	t_fixed		gravity;
	t_fixed		height;
	t_fixed		radius;
	t_fixed		rad_inter;
	t_fvec3		pos;
	t_fvec3		speed_max;
	t_fvec2		look;
	u_int32_t	sector_id;
}					t_c_ph;

typedef struct		s_c_multi_mats
{
	size_t		magic;
	ssize_t		mat[16];
}					t_c_multi_mats;

typedef struct		s_c_entity
{
	size_t		magic;
	int			id;
	t_c_ph		spawn;
	ssize_t		mats;
	int32_t		type;
	t_fixed		life;
	int			data;
}					t_c_entity;

typedef struct		s_c_player
{
	size_t			magic;
	t_c_entity		my_entity;
	u_int32_t		weapons[2];
	u_int32_t		secondary;
	u_int32_t		equiped;
}					t_c_player;

typedef struct		s_c_point
{
	size_t	magic;
	t_fvec2	point;
}					t_c_point;

typedef struct		s_c_portal
{
	size_t		magic;
	int			blocking;
	u_int32_t	from_sector;
	u_int32_t	to_sector;
	u_int32_t	from_wall;
	u_int32_t	to_wall;
	ssize_t		mat;
}					t_c_portal;

typedef struct		s_c_wall
{
	size_t		magic;
	t_fvec2		tex_pos;
	int32_t		portal;
	u_int32_t	a;
	u_int32_t	b;
	ssize_t		mat;
	t_fvec2		left_z;
	t_fvec2		right_z;
}					t_c_wall;

typedef struct		s_c_sector
{
	size_t		magic;
	u_int32_t	start;
	u_int32_t	number;
	size_t		sector_id;
	t_fvec3		floor;
	t_fvec3		floor_b;
	t_fvec3		ceiling;
	t_fvec3		ceiling_b;
	t_color		ambient;
	ssize_t		ceiling_mat;
	ssize_t		floor_mat;
	t_fvec2		tex_pos;
	t_fvec2		center;
}					t_c_sector;

typedef struct		s_c_game
{
	size_t		magic;
	size_t		ninventory;
	size_t		loc_inventory;
	size_t		nmaterials;
	size_t		loc_mats;
	size_t		loc_player;
	size_t		npoints;
	size_t		loc_points;
	size_t		nwalls;
	size_t		nuwalls;
	size_t		loc_walls;
	size_t		nsectors;
	size_t		loc_sectors;
	size_t		nportals;
	size_t		loc_portals;
	size_t		nentities;
	size_t		loc_entities;
	size_t		unique_e_id;
	size_t		ntextures;
	size_t		loc_textures;
}					t_c_game;

int					open_file(const char *file, int edit_mode,\
					size_t *filesize);
void				*dump_file(const char *file, int edit_mode, size_t *size);

size_t				id_from_p(void *p_objet, void *tab, size_t size);
void				*id_to_p(ssize_t index, void *tab, size_t size);

#endif

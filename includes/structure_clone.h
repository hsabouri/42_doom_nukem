/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure_clone.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugo <hugo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 15:58:57 by hsabouri          #+#    #+#             */
/*   Updated: 2018/12/26 16:16:50 by hugo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_CLONE_H
# define STRUCTURE_CLONE_H

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
	ssize_t			overlay;
}					t_c_mat;

typedef struct		s_c_ph
{
	t_fixed		gravity;
	t_fixed		height;
	t_fixed		radius;
	t_fvec3		pos;
	t_fvec3		speed_max;
	t_fvec2		look;
	u_int32_t	sector_id;
}					t_c_ph;

typedef struct		s_c_player
{
	t_c_ph			spawn;
	// float		life;
	// float		armor;
	// size_t		inventory;
	// size_t		ninventory;
	// uint8_t		equiped;
	// size_t		weapons[5];
}					t_c_player;

typedef struct		s_c_entity
{
	size_t		magic;
	t_c_ph		spawn;
	size_t		mat;
	//float life;
	//float  armor;
	//t_weapon weapons;
	int 		damage;
}					t_c_entity;

typedef struct		s_c_point
{
	size_t	magic;
	t_fvec2	point;
}					t_c_point;

typedef struct		s_c_portal
{
	size_t		magic;
	u_int32_t	from_sector;
	u_int32_t	to_sector;
	u_int32_t	from_wall;
	u_int32_t	to_wall;
	u_int32_t	a;
	u_int32_t	b;
}					t_c_portal;

typedef struct		s_c_wall
{
	size_t		magic;
	t_fvec2		tex_pos;
	int32_t		portal;
	u_int32_t	a;
	u_int32_t	b;
	size_t		mat;
}					t_c_wall;

typedef struct		s_c_sector
{
	size_t		magic;
	u_int32_t	start;
	u_int32_t	number;
	size_t		sector_id;
	t_fixed		floor;
	t_fixed		ceiling;
	t_color		ambient;
	size_t		ceiling_mat;
	size_t		floor_mat;
}					t_c_sector;

typedef struct		s_c_music
{
	size_t 		magic;
	size_t		length;
	size_t		content;
}					t_c_music;

typedef struct		s_c_game
{
	size_t		magic;
	t_c_player	player;
	size_t		nmaterials;
	size_t		loc_mats;
	size_t		npoints;
	size_t		loc_points;
	size_t		nwalls;
	size_t		loc_walls;
	size_t		nsectors;
	size_t		loc_sectors;
	size_t		nportals;
	size_t		loc_portals;
	size_t		nentities;
	size_t		loc_entities;
	size_t		ntextures;
	size_t		loc_textures;
	size_t		nmusic;
	size_t		loc_music;
	size_t		nsounds;
	size_t		loc_sounds;
}					t_c_game;

int					open_file(const char *file, int edit_mode,\
size_t *filesize);
void				*dump_file(const char *file, int edit_mode, size_t *size);

size_t				id_from_p(void *p_objet, void *tab, size_t size);
void				*id_to_p(ssize_t index, void *tab, size_t size);

#endif

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
# define SECTOR_MAGIC	0xCAFED00D
# define PORTAL_MAGIC	0xC11BE
# define POINT_MAGIC	0x8BADF00D
# define WALL_MAGIC		0x1B16B00B

# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <vec.h>
# include <libft.h>

typedef struct		s_c_ph
{
	t_fixed		gravity;
	t_fixed		height;
	t_fvec3		pos;
	t_fvec3		speed_max;
	t_fvec2		look;
}					t_c_ph;

typedef struct		s_c_player
{
	t_c_ph		physic;
	// float		life;
	// float		armor;
	// size_t		inventory;
	// size_t		ninventory;
	// uint8_t		equiped;
	// size_t		weapons[5];
}					t_c_player;

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
	int32_t		portal;
	u_int32_t	a;
	u_int32_t	b;
	//u_char		texture;
	//u_char		transparent;
}					t_c_wall;

typedef struct		s_c_sector
{
	size_t		magic;
	u_int32_t	start;
	u_int32_t	number;
	t_fixed		floor;
	t_fixed		ceiling;
	//t_fixed		luminosity;
}					t_c_sector;

typedef struct		s_c_game
{
	size_t		magic;
	t_c_player	player;
	size_t		sectors;
	size_t		nsectors;
	size_t		walls;
	size_t		nwalls;
	size_t		portals;
	size_t		nportals;
	size_t		points;
	size_t		npoints;
}					t_c_game;

int					open_file(const char *file, int edit_mode, size_t *filesize);
void				*dump_file(const char *file, int edit_mode, size_t *size);

#endif

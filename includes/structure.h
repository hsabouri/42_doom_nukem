/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 17:47:17 by hsabouri          #+#    #+#             */
/*   Updated: 2018/12/29 17:50:25 by hsabouri         ###   ########.fr       */
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
	t_ph		physic;
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

typedef struct			s_game
{
	t_player	player;
	t_sector	*sectors;
	size_t		nsectors;
	t_wall		*walls;
	size_t		nwalls;
	t_portal	*portals;
	size_t		nportals;
	t_vec2		*points;
	size_t		npoints;
}						t_game;

t_game					generate_map(t_game game);

#endif

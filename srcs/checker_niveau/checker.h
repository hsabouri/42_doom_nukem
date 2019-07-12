/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 16:57:41 by iporsenn          #+#    #+#             */
/*   Updated: 2019/05/22 14:03:17 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H

# define NBR_ERROR 25

typedef enum	e_error_type
{
	NO_ERROR,
	POINTS_WALL,
	POINT_PORTAL_WALL,
	MATS_WALL,
	POINTS_PORTAL,
	DANGLING_PORTAL_WALL,
	DANGLING_PORTAL_SECTOR,
	WALL_START_SECTOR,
	WALL_END_SECTOR,
	NUMBER_WALLS_SECTOR,
	MATS_FLOOR_SECTOR,
	MATS_CEIL_SECTOR,
	TEXTURES_MAT,
	HEIGHT_SECTOR,
	HEIGHT_SECTOR_NEXT,
	CONCAVE_SECTOR,
	OUTSIDE_SPAWN,
	SECTOR_PORTAL,
	WALL_PORTAL,
	ID_SECTOR,
	OVERLAY_MAT,
	PARALLEL_PORTAL,
	MATS_ENTITIES,
	BAD_SECTOR,
	MULTI_SPRITE,
}				t_error_type;

typedef struct	s_lvl_error
{
	t_elem			elem;
	t_error_type	error_type;
	int32_t			point;
	int32_t			wall;
	int32_t			portal;
	int32_t			sector;
	int32_t			mats;
	int32_t			multi_mats;
	int32_t			entities;
}				t_lvl_error;

typedef struct	s_check_sect
{
	size_t	start;
	size_t	end;
	size_t	first;
	size_t	previous;
	int		sign;
	float	angle;
	t_vec2	ab;
	t_vec2	cd;
}				t_check_sect;

typedef struct	s_check_mat
{
	size_t	nmaterials;
	t_mat	*materials;
}				t_check_mat;

void			init_error(t_lvl_error *error);
t_lvl_error		check_wall_sector(t_sector *sectors, size_t nsectors,
				size_t nwalls);
t_list			dangling_portal_wall(t_portal *portals, size_t nportals,
				t_game game);
t_list			dangling_portal_sector(t_portal *portals, size_t nportals,
				t_game game);
t_list			height_sector(t_sector *sectors, size_t nsectors);
t_list			parallel_portal(t_portal *portal, size_t nportals, t_game game);
t_list			sector_entity(t_entity *entities, size_t nentities,
				t_game game);

#endif

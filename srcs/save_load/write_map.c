/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsabouri <hsabouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 18:32:17 by iporsenn          #+#    #+#             */
/*   Updated: 2019/06/20 10:32:04 by hsabouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

void	write_mats(int fd, t_mat *mats, size_t nmats, t_img *textures)
{
	t_c_mat	s_mats;
	size_t	i;

	i = 0;
	while (i < nmats)
	{
		s_mats.magic = MAT_MAGIC + i;
		s_mats.pos = mats[i].pos;
		s_mats.sca = mats[i].sca;
		s_mats.color = mats[i].color;
		if (mats[i].texture != NULL)
			s_mats.texture = id_from_p(mats[i].texture, textures,
				sizeof(t_img));
		else
			s_mats.texture = -1;
		s_mats.mode = mats[i].mode;
		s_mats.filter = mats[i].filter;
		s_mats.frozen = mats[i].frozen;
		if (mats[i].overlay != NULL)
			s_mats.overlay = id_from_p(mats[i].overlay, mats, sizeof(t_mat));
		else
			s_mats.overlay = -1;
		write_struct(&s_mats, fd, sizeof(t_c_mat));
		i++;
	}
}

void	write_points(int fd, t_vec2 *points, size_t npoints)
{
	t_c_point	s_points;
	size_t		i;

	i = 0;
	while (i < npoints)
	{
		s_points.magic = POINT_MAGIC + i;
		s_points.point = vec2_to_fvec2(points[i]);
		write_struct(&s_points, fd, sizeof(t_c_point));
		i++;
	}
}

void	write_walls(int fd, t_wall *walls, size_t nwalls, t_mat *mats)
{
	t_c_wall	s_walls;
	size_t		i;

	i = 0;
	while (i < nwalls)
	{
		s_walls.magic = WALL_MAGIC + i;
		s_walls.tex_pos = walls[i].tex_pos;
		s_walls.portal = walls[i].portal;
		s_walls.a = walls[i].a;
		s_walls.b = walls[i].b;
		if (walls[i].mat != NULL)
			s_walls.mat = id_from_p(walls[i].mat, mats, sizeof(t_mat));
		else
			s_walls.mat = -1;
		s_walls.left_z = vec2_to_fvec2(walls[i].left_z);
		s_walls.right_z = vec2_to_fvec2(walls[i].right_z);
		write_struct(&s_walls, fd, sizeof(t_c_wall));
		i++;
	}
}

void	write_sectors(int fd, t_sector *sectors, size_t nsectors, t_mat *mats)
{
	t_c_sector	s_sectors;
	size_t		i;

	i = 0;
	while (i < nsectors)
	{
		s_sectors = (t_c_sector) {.magic = SECTOR_MAGIC + i,
			.start = sectors[i].start, .number = sectors[i].number,
			.sector_id = sectors[i].sector_id, .ambient = sectors[i].ambient,
			.floor = vec3_to_fvec3(sectors[i].floor),
			.ceiling = vec3_to_fvec3(sectors[i].ceiling),
			.floor_b = vec3_to_fvec3(sectors[i].floor_b),
			.ceiling_b = vec3_to_fvec3(sectors[i].ceiling_b),
			.ceiling_mat = (sectors[i].ceiling_mat != NULL)
				? id_from_p(sectors[i].ceiling_mat, mats, sizeof(t_mat)) : -1};
		if (sectors[i].floor_mat != NULL)
			s_sectors.floor_mat = id_from_p(sectors[i].floor_mat, mats,
				sizeof(t_mat));
		else
			s_sectors.floor_mat = -1;
		s_sectors.tex_pos = sectors[i].tex_pos;
		s_sectors.center = vec2_to_fvec2(sectors[i].center);
		write_struct(&s_sectors, fd, sizeof(t_c_sector));
		i++;
	}
}

void	write_portals(int fd, t_portal *portals, size_t nportals, t_mat *mats)
{
	t_c_portal	s_portals;
	size_t		i;

	i = 0;
	while (i < nportals)
	{
		s_portals.magic = PORTAL_MAGIC + i;
		s_portals.blocking = portals[i].blocking;
		s_portals.from_sector = portals[i].from_sector;
		s_portals.to_sector = portals[i].to_sector;
		s_portals.from_wall = portals[i].from_wall;
		s_portals.to_wall = portals[i].to_wall;
		if (portals[i].mat != NULL)
			s_portals.mat = id_from_p(portals[i].mat, mats, sizeof(t_mat));
		else
			s_portals.mat = -1;
		write_struct(&s_portals, fd, sizeof(t_c_portal));
		i++;
	}
}

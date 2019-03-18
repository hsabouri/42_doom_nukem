/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 18:32:17 by iporsenn          #+#    #+#             */
/*   Updated: 2019/02/19 18:32:18 by iporsenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <doom.h>

void	write_mats(int fd, t_mat *mats, size_t nmats, t_img *textures)
{
	t_c_mat	fmats;
	size_t	i;

	i = 0;
	while (i < nmats)
	{
		fmats.magic = MAT_MAGIC + i;
		fmats.pos = mats[i].pos;
		fmats.sca = mats[i].sca;
		fmats.color = mats[i].color;
		if (mats[i].texture != NULL)
			fmats.texture = id_from_p(mats[i].texture, textures, sizeof(t_img));
		else
			fmats.texture = -1;
		fmats.mode = mats[i].mode;
		fmats.filter = mats[i].filter;
		if (mats[i].overlay != NULL)
			fmats.overlay = id_from_p(mats[i].overlay, mats, sizeof(t_mat));
		else
			fmats.overlay = -1;
		write_struct(&fmats, fd, sizeof(t_c_mat));
		i++;
	}
}

void	write_points(int fd, t_vec2 *points, size_t npoints)
{
	t_c_point	fpoints;
	size_t		i;

	i = 0;
	while (i < npoints)
	{
		fpoints.magic = POINT_MAGIC + i;
		fpoints.point = vec2_to_fvec2(points[i]);
		write_struct(&fpoints, fd, sizeof(t_c_point));
		i++;
	}
}

void	write_walls(int fd, t_wall *walls, size_t nwalls, t_mat *mats)
{
	t_c_wall	fwalls;
	size_t		i;

	i = 0;
	while (i < nwalls)
	{
		fwalls.magic = WALL_MAGIC + i;
		fwalls.tex_pos = walls[i].tex_pos;
		fwalls.portal = walls[i].portal;
		fwalls.a = walls[i].a;
		fwalls.b = walls[i].b;
		if (walls[i].mat != NULL)
			fwalls.mat = id_from_p(walls[i].mat, mats, sizeof(t_mat));
		else
			fwalls.mat = -1;
		write_struct(&fwalls, fd, sizeof(t_c_wall));
		i++;
	}
}

void	write_sectors(int fd, t_sector *sectors, size_t nsectors, \
t_mat *mats)
{
	t_c_sector	fsectors;
	size_t		i;

	i = 0;
	while (i < nsectors)
	{
		fsectors.magic = SECTOR_MAGIC + i;
		fsectors.start = sectors[i].start;
		fsectors.number = sectors[i].number;
		fsectors.sector_id = sectors[i].sector_id;
		fsectors.floor = f_from_float(sectors[i].floor);
		fsectors.ceiling = f_from_float(sectors[i].ceiling);
		fsectors.ambient = sectors[i].ambient;
		if (sectors[i].ceiling_mat != NULL)
			fsectors.ceiling_mat = id_from_p(sectors[i].ceiling_mat, mats,\
				sizeof(t_mat));
		else
			fsectors.ceiling_mat = -1;
		if (sectors[i].floor_mat != NULL)
			fsectors.floor_mat = id_from_p(sectors[i].floor_mat, mats, \
				sizeof(t_mat));
		else
			fsectors.floor_mat = -1;
		fsectors.tex_pos = sectors[i].tex_pos;
		write_struct(&fsectors, fd, sizeof(t_c_sector));
		i++;
	}
}

void	write_portals(int fd, t_portal *portals, size_t nportals, t_mat *mats)
{
	t_c_portal	fportals;
	size_t		i;

	i = 0;
	while (i < nportals)
	{
		fportals.magic = PORTAL_MAGIC + i;
		fportals.from_sector = portals[i].from_sector;
		fportals.to_sector = portals[i].to_sector;
		fportals.from_wall = portals[i].from_wall;
		fportals.to_wall = portals[i].to_wall;
		fportals.a = portals[i].a;
		fportals.b = portals[i].b;
		if (portals[i].mat != NULL)
			fportals.mat = id_from_p(portals[i].mat, mats, sizeof(t_mat));
		else
			fportals.mat = -1;
		write_struct(&fportals, fd, sizeof(t_c_portal));
		i++;
	}
}
